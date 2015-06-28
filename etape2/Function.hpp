#ifndef FUNCTION_HPP_
# define FUNCTION_HPP_

# include <iostream>

struct		NullType
{
};

// SigTrait and partial specialization

template<typename T, typename B = NullType>
struct		SigTrait;

template<typename Ret, typename B>
struct		SigTrait<Ret (), B>
{
  typedef Ret (*fptr)();
  typedef B BB;
  typedef Ret RetType;
  typedef NullType A1Type;
  typedef NullType A2Type;
  typedef NullType A3Type;
  typedef NullType A4Type;
};

template<typename Ret, typename A1, typename B>
struct		SigTrait<Ret (A1), B>
{
  typedef Ret (*fptr)(A1);
  typedef B BB;
  typedef Ret RetType;
  typedef A1 A1Type;
  typedef NullType A2Type;
  typedef NullType A3Type;
  typedef NullType A4Type;
};

template<typename Ret, typename A1, typename A2, typename B>
struct		SigTrait<Ret (A1, A2), B>
{
  typedef Ret (*fptr)(A1, A2);
  typedef B BB;
  typedef Ret RetType;
  typedef A1 A1Type;
  typedef A2 A2Type;
  typedef NullType A3Type;
  typedef NullType A4Type;
};

template<typename Ret, typename A1, typename A2, typename A3, typename B>
struct		SigTrait<Ret (A1, A2, A3), B>
{
  typedef Ret (*fptr)(A1, A2, A3);
  typedef B BB;
  typedef Ret RetType;
  typedef A1 A1Type;
  typedef A2 A2Type;
  typedef A3 A3Type;
  typedef NullType A4Type;
};

template<typename Ret, typename A1, typename A2, typename A3, typename A4, typename B>
struct		SigTrait<Ret (A1, A2, A3, A4), B>
{
  typedef Ret (*fptr)(A1, A2, A3, A4);
  typedef B BB;
  typedef Ret RetType;
  typedef A1 A1Type;
  typedef A2 A2Type;
  typedef A3 A3Type;
  typedef A4 A4Type;
};

// ICallable interface for fptr, boost::bind, fctor

template<typename T>
class		ICallable;

template <typename Ret>
struct ICallable<Ret ()>
{
  virtual ~ICallable() {}
  virtual Ret	operator()() = 0;
};

template <typename Ret, typename A0>
struct ICallable<Ret (A0)>
{
  virtual ~ICallable() {}
  virtual Ret	operator()(A0) = 0;
};

template <typename Ret, typename A0, typename A1>
struct ICallable<Ret (A0, A1)>
{
  virtual ~ICallable() {}
  virtual Ret	operator()(A0, A1) = 0;
};

template <typename Ret, typename A0, typename A1, typename A2>
struct ICallable<Ret (A0, A1, A2)>
{
  virtual ~ICallable() {}
  virtual Ret	operator()(A0, A1, A2) = 0;
};

template <typename Ret, typename A0, typename A1, typename A2, typename A3>
struct ICallable<Ret (A0, A1, A2, A3)>
{
  virtual ~ICallable() {}
  virtual Ret	operator()(A0, A1, A2, A3) = 0;
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
  typedef typename SigTrait<T>::fptr fptr;
  fptr		m_machin_;

public:
  FuncPtr(fptr in) : m_machin_(in) {}
  virtual ~FuncPtr() {}
  Ret	operator()()
  {
    return m_machin_();
  }
  Ret	operator()(A1 a1)
  {
    return m_machin_(a1);
  }
  Ret	operator()(A1 a1, A2 a2)
  {
    return m_machin_(a1, a2);
  }
  Ret	operator()(A1 a1, A2 a2, A3 a3)
  {
    return m_machin_(a1, a2, a3);
  }
  Ret	operator()(A1 a1, A2 a2, A3 a3, A4 a4)
  {
    return m_machin_(a1, a2, a3, a4);
  }
};

template<typename T, typename F>
class	        Functor : public ICallable<T>
{
private:
  typedef typename SigTrait<T>::RetType Ret;
  typedef typename SigTrait<T>::A1Type A1;
  typedef typename SigTrait<T>::A2Type A2;
  typedef typename SigTrait<T>::A3Type A3;
  typedef typename SigTrait<T>::A4Type A4;
  F*		m_machin_;

public:
  Functor(const F& f) : m_machin_(new F(f)) {}

  virtual ~Functor() {}

  Ret	operator()()
  {
    return (*m_machin_)();
  }

  Ret	operator()(A1 a1)
  {
    return (*m_machin_)(a1);
  }

  Ret	operator()(A1 a1, A2 a2)
  {
    return (*m_machin_)(a1, a2);
  }

  Ret	operator()(A1 a1, A2 a2, A3 a3)
  {
    return (*m_machin_)(a1, a2, a3);
  }

  Ret	operator()(A1 a1, A2 a2, A3 a3, A4 a4)
  {
    return (*m_machin_)(a1, a2, a3, a4);
  }
};

template<typename T>
class	Function
{
  typedef typename SigTrait<T>::fptr fptr;
  typedef typename SigTrait<T>::RetType Ret;
  typedef typename SigTrait<T>::A1Type A1;
  typedef typename SigTrait<T>::A2Type A2;
  typedef typename SigTrait<T>::A3Type A3;
  typedef typename SigTrait<T>::A4Type A4;
  ICallable<T>* m_callable_;

public:
  // ctor
  Function() : m_callable_(NULL) {}
  Function(typename SigTrait<T>::fptr f) : m_callable_(new FuncPtr<T>(f)) {}
  template<typename F>
  Function(const F& f)
    : m_callable_(new Functor<T, F>(f))
  {
  }

  // dtor
  ~Function()
  {
    if (m_callable_)
      delete m_callable_;
  }

  // operator overloading
  Function operator=(const fptr& f)
  {
    m_callable_ = new FuncPtr<T>(f);
    return *this;
  }
  template<typename F>
  Function operator=(const F& f)
  {
    m_callable_ = new Functor<T, F>(f);
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

#endif	// !FUNCTOPM_HPP_
