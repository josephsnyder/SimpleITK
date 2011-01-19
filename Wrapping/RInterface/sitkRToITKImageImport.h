#ifndef _sitkRToITKImageImport_h
#define __sitkRToITKImageImport_h

#include "sitkMacro.h"
#include "sitkImage.h"

#include "sitkPixelIDTokens.h"

#define R_NO_REMAP /* AVOID SOME SERIOUS STUPIDITY. DO NOT REMOVE. */

#include "R.h"
#include "Rdefines.h"
#include "R_ext/Parse.h"
#include "R_ext/Rdynload.h"

namespace itk {
  namespace simple {


    class RToITKImageImport {
    public:
      typedef RToITKImageImport Self;

      Self& SetImportPointer ( SEXP );
      SEXP GetImportPointer();
      Image::Pointer Execute();
      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );

    protected:

      template < unsigned int VImageDimension >
      Image::Pointer ExecuteInternalParser( int componentType );

      // methods which utlize the EnableIf idiom to conditionally
      // instatiate ad execute the implementation
      template <typename TPixel, unsigned int VImageDimension>
      typename EnableIf<IsInstantiated<itk::Image<TPixel, VImageDimension> >::Value, Image::Pointer >::Type
      ExecuteInternal ( );
      template <typename TPixel, unsigned int VImageDimension>
      typename DisableIf<IsInstantiated<itk::Image<TPixel, VImageDimension> >::Value, Image::Pointer >::Type
      ExecuteInternal ( );

    private:

      SEXP         m_ImportPointer;
    };

  }
}

#endif
 instatiate ad execute the implementation
      template <typename TPixel, unsigned int VImageDimension>
      typename EnableIf<IsInstantiated<itk::Image<TPixel, VImageDimension> >::Value, Image::Pointer >::Type