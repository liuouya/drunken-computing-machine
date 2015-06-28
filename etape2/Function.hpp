#ifndef FUNCTION_HPP_
# define FUNCTION_HPP_

# include <iostream>

struct		NullType
{
};

template<typename T>
struct		SigTrait;

template<typename Ret, typename A1>
struct		SigTrait<Ret (A1)>
{
  typedef Ret (*fptr)(A1);
  typedef boost::_bi::bind_t<Ret, fptr, boost::_bi::list1<boost::arg<1> > > boost_type;
  typedef Ret RetType;
  typedef A1 A1Type;
  typedef NullType A2Type;
  typedef NullType A3Type;
  typedef NullType A4Type;
};

template<typename Ret, typename A1, typename A2>
struct		SigTrait<Ret (A1, A2)>
{
  typedef Ret (*fptr)(A1, A2);
  // typedef boost::_bi::bind_t<Ret, fptr, boost::_bi::list2<boost::arg<2> > > boost_type;
  typedef Ret RetType;
  typedef A1 A1Type;
  typedef A2 A2Type;
  typedef NullType A3Type;
  typedef NullType A4Type;
};

template<typename Ret, typename A1, typename A2, typename A3>
struct		SigTrait<Ret (A1, A2, A3)>
{
  typedef Ret (*fptr)(A1, A2, A3);
  // typedef boost::_bi::bind_t<Ret, fptr, boost::_bi::list2<boost::arg<2> > > boost_type;
  typedef Ret RetType;
  typedef A1 A1Type;
  typedef A2 A2Type;
  typedef A3 A3Type;
  typedef NullType A4Type;
};

template<typename Ret, typename A1, typename A2, typename A3, typename A4>
struct		SigTrait<Ret (A1, A2, A3, A4)>
{
  typedef Ret (*fptr)(A1, A2, A3, A4);
  // typedef boost::_bi::bind_t<Ret, fptr, boost::_bi::list2<boost::arg<2> > > boost_type;
  typedef Ret RetType;
  typedef A1 A1Type;
  typedef A2 A2Type;
  typedef A3 A3Type;
  typedef A4 A4Type;
};

template<typename T>
class		ICallable
{
  typedef typename SigTrait<T>::RetType Ret;
  typedef typename SigTrait<T>::A1Type A1;
  typedef typename SigTrait<T>::A2Type A2;
  typedef typename SigTrait<T>::A3Type A3;
  typedef typename SigTrait<T>::A4Type A4;
public:
  virtual ~ICallable() {}
  virtual Ret	operator()() = 0;
  virtual Ret	operator()(A1) = 0;
  virtual Ret	operator()(A1, A2) = 0;
  virtual Ret	operator()(A1, A2, A3) = 0;
  virtual Ret	operator()(A1, A2, A3, A4) = 0;
};

template<typename T>
class	        FuncPtr : public ICallable<T>
{
private:
  typedef typename SigTrait<T>::RetType Ret;
  typedef typename SigTrait<T>::A1Type A1;
  typedef typename SigTrait<T>::A2Type A2;
  typedef typename SigTrait<T>::A3Type A3;
  typedef typename SigTrait<T>::A4Type A4;
  typedef Ret (*fptr)();
  typedef Ret (*fptr1)(A1);
  typedef Ret (*fptr2)(A1, A2);
  typedef Ret (*fptr3)(A1, A2, A3);
  typedef Ret (*fptr4)(A1, A2, A3, A4);
  fptr		m_machin_;
  fptr1		m_machin1_;
  fptr2		m_machin2_;
  fptr3		m_machin3_;
  fptr4		m_machin4_;
public:
  FuncPtr(fptr in) : m_machin_(in) {}
  FuncPtr(fptr1 in) : m_machin1_(in) {}
  FuncPtr(fptr2 in) : m_machin2_(in) {}
  FuncPtr(fptr3 in) : m_machin3_(in) {}
  FuncPtr(fptr4 in) : m_machin4_(in) {}
  virtual ~FuncPtr() {}
  virtual Ret	operator()()
  {
    return m_machin_();
  }
  virtual Ret	operator()(A1 a1)
  {
    return m_machin1_(a1);
  }
  virtual Ret	operator()(A1 a1, A2 a2)
  {
    return m_machin2_(a1, a2);
  }
  virtual Ret	operator()(A1 a1, A2 a2, A3 a3)
  {
    return m_machin3_(a1, a2, a3);
  }
  virtual Ret	operator()(A1 a1, A2 a2, A3 a3, A4 a4)
  {
    return m_machin4_(a1, a2, a3, a4);
  }
};

template<typename T>
class	Function
{
  typedef typename SigTrait<T>::fptr fptr;
  // typedef typename SigTrait<T>::boost_type boost_type;
  typedef typename SigTrait<T>::RetType Ret;
  typedef typename SigTrait<T>::A1Type A1;
  typedef typename SigTrait<T>::A2Type A2;
  typedef typename SigTrait<T>::A3Type A3;
  typedef typename SigTrait<T>::A4Type A4;
  ICallable<T>* m_callable_;
  
  // type		type_;
  // fptr		f_;
  // boost_type*	bf_;
  // void*		ftor_;
public:
  // ctor
  Function() : m_callable_(NULL) {}
  Function(typename SigTrait<T>::fptr f) : m_callable_(new FuncPtr<T>(f)) {}
  // Function(boost_type bf) : m_callable(new BoostBind<T>) {}

  // dtor
  ~Function()
  {
    if (m_callable_)
      delete m_callable_;
  }

  // operator overloading
  Function operator=(const fptr& f)
  {
    std::cout << "operator=" << std::endl;
    m_callable_ = new FuncPtr<T>(f);
    return *this;
  }

  Ret		operator()()
  {
    return m_callable_->operator()();
  }
  Ret		operator()(A1 a1)
  {
    return m_callable_->operator()(a1);
  }
  Ret		operator()(A1 a1, A2 a2)
  {
    return m_callable_->operator()(a1, a2);
  }
  Ret		operator()(A1 a1, A2 a2, A3 a3)
  {
    return m_callable_->operator()(a1, a2, a3);
  }
  Ret		operator()(A1 a1, A2 a2, A3 a3, A4 a4)
  {
    return m_callable_->operator()(a1, a2, a3, a4);
  }
};

// template<typename T>
// class		Function;

// template<typename Re, typename T>
// struct			Function<Re (T)>
// {
//   typedef Re (*fptr)(T);
//   typedef boost::_bi::bind_t<Re, fptr, boost::_bi::list1<boost::arg<1> > > boost_type;
//   enum			type
//     {
//       FPTR,
//       BOOSTBIND,
//       FTOR
//     };

//   // attribute
//   type			type_;
//   fptr			f_;
//   boost_type*		bf_;
//   void*			ftor_;

//   // ctor
//   Function(fptr f) : type_(FPTR), f_(f), bf_(NULL) {}
//   Function(boost_type bf) : type_(BOOSTBIND), f_(NULL), bf_(new boost_type(bf)) {}
//   Function(void* ftor) : type_(FTOR), ftor_(ftor) {}
//   ~Function()
//   {
//     if (bf_ && type_ == BOOSTBIND)
//       delete bf_;
//   }

//   // operator overloading
//   Re			operator()(T arg)
//   {
//     if (type_ == FPTR)
//       return f_(arg);
//     else if (type_ == BOOSTBIND)
//       return boost::bind(*bf_, _1)(arg);
//     else
//       return 0;
//   }
//   Function<Re (T)>&	operator=(fptr f)
//   {
//     f_ = f;
//     return *this;
//   }
//   Function<Re (T)>&	operator=(boost_type bf)
//   {
//     bf_ = new boost_type(bf);
//     return *this;
//   }
// };

#endif	// !FUNCTOPM_HPP_
