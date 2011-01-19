#ifdef _MFC_VER
#pragma warning(disable:4996)
#endif

#include "sitkRToITKImageImport.h"
#include <itkRToITKImageImport.h>
#include <string>



namespace itk {
  namespace simple {

    RToITKImageImport& RToITKImageImport::SetImportPointer ( SEXP variable ) {
      this->m_ImportPointer = variable;
      return *this;
    }

    Image::Pointer RToITKImageImport::Execute () {
      Image::Pointer image = NULL;
 
      // get output information about input image
    unsigned int dimension = 2;
    int componentType = TYPEOF( this->m_ImportPointer );
    switch (dimension)
      {
      case 2:
        image = this->ExecuteInternalParser<2>( componentType );
        break;
      case 3:
        image = this->ExecuteInternalParser<3>( componentType );
        break;
      }
       
    if ( image.IsNull() )
      {
      sitkExceptionMacro( "Unable to import SEXP variable." << "\"" );
      }

    return image;
}


template < unsigned int VImageDimension >
Image::Pointer RToITKImageImport::ExecuteInternalParser(int componentType )
{
    switch(componentType)
      {
    case INTSXP:
      return this->ExecuteInternal< int32_t, VImageDimension >( );
      break;
    case REALSXP:
      return this->ExecuteInternal< double, VImageDimension >( );
      break;
    default:
      return NULL;
    }
}

  template <typename TPixel, unsigned int VImageDimension>
  typename EnableIf<IsInstantiated<itk::Image<TPixel, VImageDimension> >::Value, Image::Pointer >::Type
  RToITKImageImport::ExecuteInternal( void )
  {

    typedef itk::Image<TPixel, VImageDimension>        ImageType;

    typedef itk::RToITKImageImport<TPixel, VImageDimension> Importer;

    // if the InstantiatedToken is correctly implemented this should
    // not occour
    assert( ImageTypeToPixelIDValue<ImageType>::Result != (int)sitkUnknown );

    typename Importer::Pointer importer = Importer::New();
    importer->SetImportPointer(this->m_ImportPointer);
    importer->Update();
    typename Image::Pointer image = new Image( importer->GetOutput() );
    return image;
  }

  template <typename TPixel, unsigned int VImageDimension>
  typename DisableIf<IsInstantiated<itk::Image<TPixel, VImageDimension> >::Value, Image::Pointer >::Type
  RToITKImageImport::ExecuteInternal( void )
  {
    typedef itk::Image<TPixel, VImageDimension>        ImageType;

    sitkExceptionMacro( << "PixelType is not supported!" << std::endl
                        << "Pixel Type: "
                        << GetPixelIDValueAsString( ImageTypeToPixelIDValue<ImageType>::Result ) << std::endl
                        << "Refusing to load! " << std::endl );
    return NULL;
  }

  }
}
Instantiated<itk::Image<TPixel, VImageDimension> >::Value, Image::Pointer >::Type
  RToITKImageImport::ExecuteInternal( void )
  {
    typedef itk::Image<TPixel, VImageDimension>        ImageType;

    sitkExceptionMacro( << "PixelType is not supported!" << std::endl
                        << "Pixel Type: "
                        << GetPixelIDValueAsString( ImageTypeToPixelIDValue<ImageType>::Result ) << std