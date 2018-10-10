

// smart pointers are defined in the <memory> header.
#include <memory>

#include <iostream>
#include <utility>

using namespace std;

class Foo {
  static long long count;
  long long* id = nullptr;
  long long orig_value;
public:
  Foo(): id(new long long(count++)), orig_value(*id)
  {
    cout << "Foo" << *id << ": orig" << orig_value << " constructed!" << endl;
  }

  Foo(const Foo& other): id(new long long(count++)),
                         orig_value(other.orig_value)
  {
    cout << "Foo" << *id << ": orig" << orig_value << " copied!" << endl;
  }

  Foo(Foo&& other): id(other.id), orig_value(other.orig_value)
  {
    other.id = nullptr;
    cout << "Foo" << *id << ": orig" << orig_value << " moved!" << endl;
  }

  ~Foo()
  {
    if (id) {
    cout << "Foo" << *id << ": orig" << orig_value << " destroyed!" << endl;
      delete id;
    } else {
      cout << "Derelict Foo destructed!" << endl;
    }
  }
};

long long Foo::count = 0;


int main()
{
  cout << "creating a raw Foo object" << endl;
  Foo foo;

  { // braces for scope
    cout << "assigning the raw object directly makes a copy of the object."
         << endl;
    Foo foo1 = foo;
    cout << "assigning the raw object via a r-value (move) reference will use "
            "the move constructor instead, which should transfer ownership of "
            "all fields from foo1 to foo2." << endl;
    Foo foo2 = std::move(foo1);
    cout << "observe the now different states of the two destroyed Foo "
            "objects." << endl;
  } // note local variabls are destroyed when they leave scope.

  {
    cout << "creating a raw Foo pointer" << endl;
    Foo* ptr = new Foo;

    cout << "raw pointer reassignment, leaking previous value!" << endl;
    ptr = new Foo;

    cout << "must manually delete raw Foo pointer to avoid (further) leak."
         << endl;
    delete ptr;
    cout << "Note that the pointer still holds the memory address, even if "
            "the pointer is no longer valid: (ptr == "
         << ptr << ")"<< endl;
  }

  {
    cout << "creating sptr0 as an empty shared_ptr. note that this does not "
            "create a Foo object" << endl;
    shared_ptr<Foo> sptr0;
    cout << "creating sptr1 via the standard constructor" << endl;
    shared_ptr<Foo> sptr1(new Foo);
    cout << "creating sptr2 via make_shared" << endl;
    shared_ptr<Foo> sptr2 = make_shared<Foo>();

    cout << "copying a shared_ptr is legal, and does not copy the object, "
            "only the reference to the object." << endl;
    sptr0 = sptr1;

    cout << "moving a shared_ptr is legal, and also does not copy the object. "
            "however, moving invalidates the shared_ptr that is moved, and if "
            "that shared_ptr was the last reference, it deletes the managed "
            "pointer." << endl;
    sptr0 = std::move(sptr2);

    cout << "you can set a shared_ptr to nullptr to remove it as a reference "
            "to the managed pointer. note that this deletes the object moved "
            "from sptr2" << endl;
    sptr0 = nullptr;

    cout << "you can also call shared_ptr<>::reset() for the same effect. "
            "note that nothing is destroyed, since sptr0 was empty from the "
            "last statement anyway." << endl;
    sptr0.reset();

    cout << "note that as we exit scope, the shared_ptrs are destroyed, and "
            "destroy their managed objects, since no references remain."
         << endl;
  }

  {
    cout << "creating a unique_ptr reference to a Foo object." << endl;
    unique_ptr<Foo> uptr1(new Foo);

    // make_unique is not actually available until C++14. they forgot
    // to include it in the spec.

    cout << "copying a unique_ptr is illegal, since that would make it not "
            "unique." << endl;
    // unique_ptr<Foo> invalid = uptr1; // so we comment this illegal line

    cout << "moving a unique_ptr is legal, since only one reference survives "
            "the move." << endl;
    unique_ptr<Foo> uptr2 = std::move(uptr1);
  }

  {
    cout << "creating a shared_ptr to a Foo." << endl;
    shared_ptr<Foo> strong_ref = make_shared<Foo>();

    cout << "creating a weak_ptr off that shared_ptr" << endl;
    weak_ptr<Foo> weak_ref(strong_ref);

    cout << "weak_ptr is " << (weak_ref.expired() ? "dead" : "alive")
         << " right now." << endl;

    cout << "copying another Foo using the weak_ptr" << endl;
    Foo copy = *(weak_ref.lock());

    cout << "destroying the backing shared_ptr." << endl;
    strong_ref.reset();


    cout << "weak_ptr is " << (weak_ref.expired() ? "dead" : "alive")
         << " right now." << endl;
  }
}
