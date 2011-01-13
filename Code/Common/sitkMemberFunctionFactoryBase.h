#ifndef __sitkMemberFunctionFactoryBase_h
#define __sitkMemberFunctionFactoryBase_h

#include "sitkConfigure.h"

#if defined SITK_HAS_STLTR1_TR1_FUNCTIONAL
#include <tr1/functional>
#elif defined SITK_HAS_STLTR1_FUNCTIONAL
#include <functional>
#else
#error "No system tr1 functional available"
#endif

#include "sitkPixelIDTypes.h"
#include "sitkMacro.h"
#include "sitkNonCopyable.h"

#include "FunctionTraits.h"

namespace itk
{
namespace simple
{

// this namespace is internal classes not part of the external simple ITK interface
namespace detail {


template< typename TMemberFunctionPointer, unsigned int TArity = ::detail::FunctionTraits<TMemberFunctionPointer>::arity>
class MemberFunctionFactoryBase;


/**
 * \brief A base class for the MemberFunctionFactory
 *
 *  This class is for specialization needed for different arity for
 *  the templated member function pointer
 */
template< typename TMemberFunctionPointer>
class MemberFunctionFactoryBase<TMemberFunctionPointer, 1> :
    protected NonCopyable
{
protected:

  typedef TMemberFunctionPointer                                               MemberFunctionType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ClassType     ObjectType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ResultType    MemberFunctionResultType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument0Type MemberFunctionArgumentType;


  MemberFunctionFactoryBase( void ) { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object */
  typedef std::tr1::function< MemberFunctionResultType ( MemberFunctionArgumentType ) > FunctionObjectType;


protected:

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object.
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace std::tr1::placeholders;

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return std::tr1::bind( pfunc,objectPointer, _1 );
    }

  // array of pointers to member functions
  FunctionObjectType  m_PFunction3[ typelist::Length< InstantiatedPixelIDTypeList >::Result ];
  FunctionObjectType  m_PFunction2[ typelist::Length< InstantiatedPixelIDTypeList >::Result ];

private:

  MemberFunctionFactoryBase * operator=(  MemberFunctionFactoryBase & );  // Not Implemented
  MemberFunctionFactoryBase( const  MemberFunctionFactoryBase& );  // Not Implemented
};


template< typename TMemberFunctionPointer>
class MemberFunctionFactoryBase<TMemberFunctionPointer, 2> :
    protected NonCopyable
{
protected:

  typedef TMemberFunctionPointer                                               MemberFunctionType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ResultType    MemberFunctionResultType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument0Type MemberFunctionArgument0Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument1Type MemberFunctionArgument1Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ClassType     ObjectType;


  MemberFunctionFactoryBase( void ) { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object
   */
  typedef std::tr1::function< MemberFunctionResultType ( MemberFunctionArgument1Type,  MemberFunctionArgument0Type) > FunctionObjectType;


protected:

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace std::tr1::placeholders;

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return std::tr1::bind( pfunc, objectPointer, _1, _2 );
    }

  // array of pointers to member functions
  FunctionObjectType  m_PFunction3[ typelist::Length< InstantiatedPixelIDTypeList >::Result ];
  FunctionObjectType  m_PFunction2[ typelist::Length< InstantiatedPixelIDTypeList >::Result ];

private:

  MemberFunctionFactoryBase * operator=(  MemberFunctionFactoryBase & );  // Not Implemented
  MemberFunctionFactoryBase( const  MemberFunctionFactoryBase& );  // Not Implemented
};


template< typename TMemberFunctionPointer>
class MemberFunctionFactoryBase<TMemberFunctionPointer, 3> :
    protected NonCopyable
{
protected:

  typedef TMemberFunctionPointer                                               MemberFunctionType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ResultType    MemberFunctionResultType;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument0Type MemberFunctionArgument0Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument1Type MemberFunctionArgument1Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::Argument2Type MemberFunctionArgument2Type;
  typedef typename ::detail::FunctionTraits<MemberFunctionType>::ClassType     ObjectType;


  MemberFunctionFactoryBase( void ) { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object */
  typedef std::tr1::function< MemberFunctionResultType ( MemberFunctionArgument2Type, MemberFunctionArgument1Type,  MemberFunctionArgument0Type) > FunctionObjectType;


protected:

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace std::tr1::placeholders;

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return std::tr1::bind( pfunc, objectPointer, _1, _2, _3 );
    }

  // array of pointers to member functions
  FunctionObjectType  m_PFunction3[ typelist::Length< InstantiatedPixelIDTypeList >::Result ];
  FunctionObjectType  m_PFunction2[ typelist::Length< InstantiatedPixelIDTypeList >::Result ];

private:

  MemberFunctionFactoryBase * operator=(  MemberFunctionFactoryBase & );  // Not Implemented
  MemberFunctionFactoryBase( const  MemberFunctionFactoryBase& );  // Not Implemented
};


} // end namespace detail
} // end namespace simple
} // end namespace itk

#endif // __sitkMemberFunctionFactoryBase_h
