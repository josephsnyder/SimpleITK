
#include <SimpleITK.h>
#include <sitkCastImageFilter.h>

int main ( int argc, char* argv[] ) {

  if ( argc < 4 ) {
    std::cerr << "Usage: " << argv[0] << " <input> <sigma> <output>\n";
    return 1;
  }

  itk::simple::Image::Pointer image;

  itk::simple::ImageFileReader reader;
  reader.SetFilename ( std::string ( argv[1] ) );
  image = reader.Execute();

  itk::simple::PixelIDValueType pixelID = image->GetPixelIDValue();

  itk::simple::RecursiveGaussianImageFilter gaussian;
  gaussian.SetSigma ( atof ( argv[2] ) );
  image = gaussian.Execute ( image );

  itk::simple::CastImageFilter caster;
  image = caster.SetOutputPixelType( pixelID ).Execute( image );

  itk::simple::ImageFileWriter writer;
  writer.SetFilename ( std::string ( argv[3] ) );
  writer.Execute ( image );

  return 0;
}
