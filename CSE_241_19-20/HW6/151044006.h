class GTUContainer {
   public:
      virtual void empty() = 0;
      virtual void size() = 0;
      virtual void maxsize() = 0;
      virtual void insert() = 0;
      virtual void erase() = 0;
      virtual void clear() = 0;
      virtual void begin() = 0;
      virtual void end() = 0;
};

class GTUSet :public GTUContainer {
   public:
      virtual void empty(){

      }
      virtual void size(){

      }
      virtual void maxsize(){

      }
      virtual void insert(){

      }
      virtual void erase(){

      }
      virtual void clear(){

      }
      virtual void begin(){

      }
      virtual void end(){

      }
};

class GTUVector :public GTUContainer {
   public:
      virtual void empty(){

      }
      virtual void size(){

      }
      virtual void maxsize(){

      }
      virtual void insert(){

      }
      virtual void erase(){

      }
      virtual void clear(){

      }
      virtual void begin(){

      }
      virtual void end(){
          
      }
};