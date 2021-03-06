#include "sitkImage.h"
#include "sitkImage.txx"

namespace {

}

namespace itk
{
  namespace simple
  {

    template<class TImageType>
    typename EnableIf<IsBasic<TImageType>::Value>::Type
    Image::AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth )
    {
      typename TImageType::IndexType  index;
      typename TImageType::SizeType   size;
      typename TImageType::RegionType region;
      index.Fill ( 0 );
      size.Fill(1);
      size[0] = Width;
      size[1] = Height;
      if ( TImageType::ImageDimension > 2 ) {
      assert(Depth != 0 );
        size[2] = Depth;
      }
      region.SetSize ( size );
      region.SetIndex ( index );
      typename TImageType::Pointer image = TImageType::New();
      image->SetRegions ( region );
      image->Allocate();
      image->FillBuffer ( 0.0 );
      m_PimpleImage.reset( new PimpleImage<TImageType>( image ) );
    }

  template<class TImageType>
  typename EnableIf<IsVector<TImageType>::Value>::Type
  Image::AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth )
  {
    typename TImageType::IndexType  index;
    typename TImageType::SizeType   size;
    typename TImageType::RegionType region;
    typename TImageType::PixelType  zero;

    index.Fill ( 0 );
    size.Fill(1);
    size[0] = Width;
    size[1] = Height;
    if ( TImageType::ImageDimension > 2 )
      {
      assert(Depth != 0 );
      size[2] = Depth;
      }
    region.SetSize ( size );
    region.SetIndex ( index );

    zero.SetSize( TImageType::ImageDimension );
    zero.Fill( 0.0 );


    typename TImageType::Pointer image = TImageType::New();
    image->SetRegions ( region );
    image->SetVectorLength( TImageType::ImageDimension );
    image->Allocate();
    image->FillBuffer ( zero );
    m_PimpleImage.reset( new PimpleImage<TImageType>( image ) );
  }

  template<class TImageType>
  typename EnableIf<IsLabel<TImageType>::Value>::Type
  Image::AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth )
  {
    typename TImageType::IndexType  index;
    typename TImageType::SizeType   size;
    typename TImageType::RegionType region;

    index.Fill ( 0 );
    size.Fill(1);
    size[0] = Width;
    size[1] = Height;
    if ( TImageType::ImageDimension > 2 )
      {
      assert(Depth != 0 );
      size[2] = Depth;
      }
    region.SetSize ( size );
    region.SetIndex ( index );

    typename TImageType::Pointer image = TImageType::New();
    image->SetRegions ( region );
    image->Allocate();
    image->SetBackgroundValue( 0 );
    m_PimpleImage.reset( new PimpleImage<TImageType>( image ) );
  }


    void Image::Allocate ( uint64_t Width, uint64_t Height, uint64_t Depth, PixelIDValueEnum ValueEnum ) {
      // Allocate an image

      detail::MemberFunctionFactory<MemberFunctionType> allocateMemberFactory(this);
      allocateMemberFactory.RegisterMemberFunctions< PixelIDTypeList, 3,  AllocateAddressor > ();
      allocateMemberFactory.RegisterMemberFunctions< PixelIDTypeList, 2,  AllocateAddressor > ();

      if ( ValueEnum == sitkUnknown )
        {
        sitkExceptionMacro( "Unable to construct image of unsupported pixel type" );
        }

      PixelIDValueType type = ValueEnum;
      if ( Depth == 0 ) {
        allocateMemberFactory.GetMemberFunction( type, 2 )( Width, Height, Depth );
      } else {
        allocateMemberFactory.GetMemberFunction( type, 3 )( Width, Height, Depth );
      }
    }

    Image::Image( uint64_t Width, uint64_t Height, PixelIDValueEnum ValueEnum ) {
      Allocate ( Width, Height, 0, ValueEnum );
    }
    Image::Image( uint64_t Width, uint64_t Height, uint64_t Depth, PixelIDValueEnum ValueEnum ) {
      Allocate ( Width, Height, Depth, ValueEnum );
    }

    itk::DataObject::Pointer Image::GetImageBase( void )
    {
      assert( m_PimpleImage.get() );
      return m_PimpleImage->GetDataBase();
    }

    itk::DataObject::ConstPointer Image::GetImageBase( void ) const
    {
      assert( m_PimpleImage.get() );
      return m_PimpleImage->GetDataBase().GetPointer();
    }

    PixelIDValueType Image::GetPixelIDValue( void ) const
    {
      return this->m_PimpleImage->GetPixelIDValue();
    }

    unsigned int Image::GetDimension( void ) const
    {
      return this->m_PimpleImage->GetDimension();
    }

    std::string Image::GetPixelIDTypeAsString( void ) const
    {
      return std::string( GetPixelIDValueAsString( this->GetPixelIDValue() ) );
    }

    std::string Image::ToString( void )
    {
      return this->m_PimpleImage->ToString();
    }

    uint64_t Image::GetWidth( void )
    {
      return this->m_PimpleImage->GetWidth();
    }

    uint64_t Image::GetHeight( void )
    {
      return this->m_PimpleImage->GetHeight();
    }

    uint64_t Image::GetDepth( void )
    {
      return this->m_PimpleImage->GetDepth();
    }

    PixelContainer::Pointer Image::GetPixelContainer()
    {
      return this->m_PimpleImage->GetPixelContainer();
    }

    /*
    void Image::Show(const std::string name) const
    {
      // Try to find ImageJ, write out a file and open
#if defined(__WIN32__)
      // Windows
#elseif defined(__APPLE__)
      // Mac
      char *filename = malloc ( sizeof(char) * (100 + name.size()) );
      sprintf ( filename, "/tmp/%s-XXXXX.nrrd", name.c_str() );
      mktemp ( filename );
      ImageFileWriter().SetFilename ( filename ).Execute ( this );
      std::cout << "Show Filename: " << filename << std::endl;
#else
      // Linux
#endif
    }
    */

  }
}
