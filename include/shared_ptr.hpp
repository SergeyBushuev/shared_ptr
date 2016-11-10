template<typename T>
class shared_ptr {
public:
   explicit shared_ptr(T * ptr = nullptr);

   shared_ptr( shared_ptr const & );
   auto operator =( shared_ptr const & ) -> shared_ptr &;
   shared_ptr( shared_ptr && );
   auto operator =( shared_ptr && ) -> shared_ptr&;
   ~shared_ptr();

   auto reset() -> void;

   auto get() -> T *;
   auto use_count() -> size_t;
   auto unique() -> bool;

   auto operator*() -> T &;
   auto operator->() -> T *;  
   operator bool();
};
