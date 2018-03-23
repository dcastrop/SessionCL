#ifndef __CLTY__
#define __CLTY__

using namespace std;

namespace clty {

  class CltyVisitor;

  class Stmt {
  public:
    virtual void accept(class CltyVisitor &v) = 0;
  };

  class LetIn : public Stmt {
  public:
    string idl;
    string chan;
    unsigned int num;
    void accept(class CltyVisitor &v);
  };

  class Prefix : public Stmt {
  public:
    virtual void accept(class CltyVisitor &v);
  };

  class Send : public Prefix {
    string chan;
  };

  class Recv : public Prefix {
    string chan;
  };

  class Tau : public Prefix {
  };

  class Close : public Stmt {
  public:
    string chan;
  };

  class Call : public Stmt {
  public:
    string id;
    list<string> param;
  };

  class Spawn : public Stmt {
  public:
    string id;
    list<string> param;
  };

  class IfElse : public Stmt {
  public:
    list<Stmt> sthen;
    list<Stmt> selse;
  };

  class Case {
  public:
    Prefix prefix;
    list<Stmt> cont;
  };

  class Select : public Stmt {
  public:
    list<Case> cases;
  };

  class Body {
  public:
    list<Stmt> stmt;
    };

  class Defn {
  public:
    string id;
    list<string> param;
    Body body;
  };


  class Program {
  public:
    list<Defn> defns;
  };
}

#endif
