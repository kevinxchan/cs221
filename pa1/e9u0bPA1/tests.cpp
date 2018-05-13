#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linkedlist.h"
#include "kebab.h"
#include "grill.h"

#include <string>
#include <vector>

// The tests below leak memory, but that's probably okay.

TEST_CASE("Kebab.addIngredient", "[Kebab][addIngredient]") {
  Kebab k;
  std::string contents;

  SECTION("empty skewer produces empty string") {
    contents = k.listIngredients();
    REQUIRE(contents == "");
  }

  SECTION("invalid ingredients not added") {
    k.addIngredient('V');
    k.addIngredient('%');
    k.addIngredient('\n');
    contents = k.listIngredients();
    REQUIRE(contents == "");
  }

  SECTION("insertion order is preserved when adding ingredients") {
    k.addIngredient('b');
    k.addIngredient('B');
    k.addIngredient('t');
    k.addIngredient('m');
    k.addIngredient('p');
    contents = k.listIngredients();
    REQUIRE(((contents == "bBtmp") || (contents == "pmtBb")));
  }

  SECTION("number of ingredients does not exceed SKEWER_SIZE") {
    k.addIngredient('b');
    k.addIngredient('B');
    k.addIngredient('t');
    k.addIngredient('T');
    k.addIngredient('m');
    k.addIngredient('M');
    k.addIngredient('p');
    k.addIngredient('P');
    k.addIngredient('s');
    k.addIngredient('S');
    contents = k.listIngredients();
    REQUIRE(((contents == "bBtTmMpP") || (contents == "PpMmTtBb")));
  }
}

TEST_CASE("Kebab.buildKebab", "[Kebab][buildKebab]") {
  Kebab k;
  std::string contents;

  SECTION("empty string input produces empty string") {
    k.buildKebab("");
    contents = k.listIngredients();
    REQUIRE(contents == "");
  }

  SECTION("invalid ingredients not added") {
    k.buildKebab("be7b!");
    contents = k.listIngredients();
    REQUIRE(contents == "bb");
  }

  SECTION("ingredient order of input string is preserved") {
    k.buildKebab("bBtmp");
    contents = k.listIngredients();
    REQUIRE(((contents == "bBtmp") || (contents == "pmtBb")));
  }

  SECTION("number of ingredients does not exceed SKEWER_SIZE") {
    k.buildKebab("bBtTmMpPsS");
    contents = k.listIngredients();
    REQUIRE(((contents == "bBtTmMpP") || (contents == "PpMmTtBb")));
  }
}

TEST_CASE("Kebab.numMeats", "[Kebab][numMeats]") {
  Kebab k1;  // empty kebab
  Kebab k2;  // non-empty, contains no meat
  Kebab k3;  // contains a single meat as only ingredient
  Kebab k4;  // contains a single meat among multiple ingredients
  Kebab k5;  // contains multiple (3) meats as only ingredient
  Kebab k6;  // contains multiple (4) meats among multiple ingredients
  Kebab k7;  // contains the maximum number (8) of meats

              // set up each Kebab
              // use addIngredient in case of errors with buildKebab
  k2.addIngredient('t');  k2.addIngredient('M');  k2.addIngredient('p');
  k2.addIngredient('S');  k2.addIngredient('T');

  k3.addIngredient('B');

  k4.addIngredient('T');  k4.addIngredient('m');  k4.addIngredient('P');
  k4.addIngredient('b');  k4.addIngredient('S');

  k5.addIngredient('b');  k5.addIngredient('B');  k5.addIngredient('B');

  k6.addIngredient('S');  k6.addIngredient('P');  k6.addIngredient('b');
  k6.addIngredient('t');  k6.addIngredient('B');  k6.addIngredient('b');
  k6.addIngredient('M');  k6.addIngredient('B');

  k7.addIngredient('b');  k7.addIngredient('b');  k7.addIngredient('B');
  k7.addIngredient('b');  k7.addIngredient('B');  k7.addIngredient('B');
  k7.addIngredient('b');  k7.addIngredient('B');

  SECTION("correctly answers when there are no meat items") {
    REQUIRE(k1.numMeats() == 0);
    REQUIRE(k2.numMeats() == 0);
  }

  SECTION("Correctly answers when there is exactly 1 meat item") {
    REQUIRE(k3.numMeats() == 1);
    REQUIRE(k4.numMeats() == 1);
  }

  SECTION("Correctly answers when there are more than 1 meat item") {
    REQUIRE(k5.numMeats() == 3);
    REQUIRE(k6.numMeats() == 4);
    REQUIRE(k7.numMeats() == 8);
  }
}

TEST_CASE("Kebab.hasSameIngredients", "[Kebab][hasSameIngredients]") {
  // wanted kebabs
  Kebab k1;  // b
  Kebab k2;  // bBt
  Kebab k3;  // tm
  Kebab k4;  // bmss
  Kebab k5;  // Pss

              // available kebabs
  Kebab k6;  // spTmbS
  Kebab k7;  // tmMsps
  Kebab k8;  // pPbTPB
  Kebab k9;  // mSpbBM
  Kebab k10; // mMmsmMBS
  Kebab k11; // (empty)

              // set up each Kebab
              // using addIngredient in case of errors with buildKebab
  k1.addIngredient('b');

  k2.addIngredient('b');  k2.addIngredient('B');  k2.addIngredient('t');

  k3.addIngredient('t');  k3.addIngredient('m');

  k4.addIngredient('b');  k4.addIngredient('m');
  k4.addIngredient('s');  k4.addIngredient('s');

  k5.addIngredient('P');  k5.addIngredient('s');  k5.addIngredient('s');

  k6.addIngredient('s');  k6.addIngredient('p');  k6.addIngredient('T');
  k6.addIngredient('m');  k6.addIngredient('b');  k6.addIngredient('S');

  k7.addIngredient('t');  k7.addIngredient('m');  k7.addIngredient('M');
  k7.addIngredient('s');  k7.addIngredient('p');  k7.addIngredient('s');

  k8.addIngredient('p');  k8.addIngredient('P');  k8.addIngredient('b');
  k8.addIngredient('T');  k8.addIngredient('P');  k8.addIngredient('B');

  k9.addIngredient('m');  k9.addIngredient('S');  k9.addIngredient('p');
  k9.addIngredient('b');  k9.addIngredient('B');  k9.addIngredient('M');

  k10.addIngredient('m');  k10.addIngredient('M');  k10.addIngredient('m');
  k10.addIngredient('s');  k10.addIngredient('m');  k10.addIngredient('M');
  k10.addIngredient('B');  k10.addIngredient('S');

  SECTION("does not match if missing ingredients") {
    REQUIRE_FALSE(k11.hasSameIngredients(k1));
    REQUIRE_FALSE(k11.hasSameIngredients(k2));
    REQUIRE_FALSE(k11.hasSameIngredients(k3));
    REQUIRE_FALSE(k11.hasSameIngredients(k4));
    REQUIRE_FALSE(k11.hasSameIngredients(k5));

    REQUIRE_FALSE(k6.hasSameIngredients(k2));
    REQUIRE_FALSE(k7.hasSameIngredients(k1));
    REQUIRE_FALSE(k7.hasSameIngredients(k2));
    REQUIRE_FALSE(k7.hasSameIngredients(k4));
    REQUIRE_FALSE(k8.hasSameIngredients(k3));
    REQUIRE_FALSE(k8.hasSameIngredients(k4));
    REQUIRE_FALSE(k8.hasSameIngredients(k5));
    REQUIRE_FALSE(k9.hasSameIngredients(k2));
    REQUIRE_FALSE(k9.hasSameIngredients(k3));
    REQUIRE_FALSE(k9.hasSameIngredients(k4));
    REQUIRE_FALSE(k9.hasSameIngredients(k5));
    REQUIRE_FALSE(k10.hasSameIngredients(k2));
    REQUIRE_FALSE(k10.hasSameIngredients(k3));
    REQUIRE_FALSE(k10.hasSameIngredients(k5));
  }

  SECTION("matches if all requested ingredients present") {
    REQUIRE(k6.hasSameIngredients(k1));
    REQUIRE(k6.hasSameIngredients(k3));
    REQUIRE(k6.hasSameIngredients(k4));
    REQUIRE(k6.hasSameIngredients(k5));
    REQUIRE(k7.hasSameIngredients(k3));
    REQUIRE(k7.hasSameIngredients(k5));
    REQUIRE(k8.hasSameIngredients(k1));
    REQUIRE(k8.hasSameIngredients(k2));
    REQUIRE(k9.hasSameIngredients(k1));
    REQUIRE(k10.hasSameIngredients(k1));
    REQUIRE(k10.hasSameIngredients(k4));
  }
}

TEST_CASE("LinkedList", "[LinkedList]") {
    LinkedList emptyList;

    LinkedList oneItemList;

    Kebab *item = new Kebab();
    item->addIngredient('b');
    item->addIngredient('p');
    item->addIngredient('m');

    oneItemList.insertFront(item);

    SECTION("starts out empty") {
        REQUIRE(emptyList.size() == 0);
        REQUIRE(emptyList.isEmpty());
    }

    SECTION("copy constructor deep copies the list") {
        LinkedList copiedList(oneItemList);

        REQUIRE(copiedList.size() == 1);
        REQUIRE_FALSE(copiedList.isEmpty());
        REQUIRE(copiedList.contains(*item));
        REQUIRE_FALSE(copiedList.elementAt(0) == item);
        REQUIRE(copiedList.elementAt(0)->listIngredients() == item->listIngredients());
    }

    SECTION("assignment operator copies a list") {
        LinkedList copiedList;
        copiedList.operator=(oneItemList);

        REQUIRE(copiedList.size() == 1);
        REQUIRE_FALSE(copiedList.isEmpty());
        REQUIRE(copiedList.contains(*item));
        REQUIRE_FALSE(copiedList.elementAt(0) == item);
        REQUIRE(copiedList.elementAt(0)->listIngredients() == item->listIngredients());
    }

    SECTION("assignment operator is noop if called on itself") {
        oneItemList.operator=(oneItemList);

        REQUIRE(oneItemList.size() == 1);
        REQUIRE(oneItemList.elementAt(0) == item);
    }
}

TEST_CASE("LinkedList.insertAt", "[LinkedList][insertAt]") {
    LinkedList list;

    Kebab *item1 = new Kebab();
    item1->addIngredient('b');
    item1->addIngredient('p');
    item1->addIngredient('m');

    Kebab *item2 = new Kebab();
    item2->addIngredient('m');
    item2->addIngredient('m');
    item2->addIngredient('m');

    Kebab *item3 = new Kebab();
    item2->addIngredient('p');
    item3->addIngredient('p');
    item3->addIngredient('p');

    SECTION("returns false with an invalid index") {
        REQUIRE_FALSE(list.insertAt(item1, 100));
        REQUIRE(list.isEmpty());
    }

    SECTION("inserts into the front of an empty list") {
        REQUIRE(list.insertAt(item1, 0));

        REQUIRE(list.size() == 1);
        REQUIRE_FALSE(list.isEmpty());

        REQUIRE(list.contains(*item1));
        REQUIRE(list.elementAt(0) == item1);
    }

    SECTION("inserts before specified element") {
        list.insertFront(item1);
        
        REQUIRE(list.insertAt(item2, 0));

        REQUIRE(list.size() == 2);
        REQUIRE(list.elementAt(0) == item2);
        REQUIRE(list.elementAt(1) == item1);
    }

    SECTION("inserts between elements") {
        list.insertFront(item1);
        list.insertFront(item2);
        
        REQUIRE(list.insertAt(item3, 1));

        REQUIRE(list.size() == 3);
        REQUIRE(list.elementAt(0) == item2);
        REQUIRE(list.elementAt(1) == item3);
        REQUIRE(list.elementAt(2) == item1);
    }
}

TEST_CASE("LinkedList.removeAt", "[LinkedList][removeAt]") {
    LinkedList list;
    
    Kebab *item1 = new Kebab();
    item1->addIngredient('b');
    item1->addIngredient('p');
    item1->addIngredient('m');

    Kebab *item2 = new Kebab();
    item2->addIngredient('m');
    item2->addIngredient('m');
    item2->addIngredient('m');

    Kebab *item3 = new Kebab();
    item2->addIngredient('p');
    item3->addIngredient('p');
    item3->addIngredient('p');

    list.insertFront(item1);
    list.insertFront(item2);
    list.insertFront(item3);

    SECTION("removing an invalid element produces null") {
        REQUIRE(list.removeAt(100) == nullptr);
    }

    SECTION("removing the first element results in a list with two elements left") {
        REQUIRE(list.removeAt(0) == item3);

        REQUIRE(list.size() == 2);
        REQUIRE(list.elementAt(0) == item2);
        REQUIRE(list.elementAt(1) == item1);
    }

    SECTION("removing an element in the middle") {
        REQUIRE(list.removeAt(1) == item2);

        REQUIRE(list.size() == 2);
        REQUIRE(list.elementAt(0) == item3);
        REQUIRE(list.elementAt(1) == item1);
    }

    SECTION("removing the all items in a list results in an empty list") {
        REQUIRE(list.removeAt(0) == item3);
        REQUIRE(list.removeAt(0) == item2);
        REQUIRE(list.removeAt(0) == item1);

        REQUIRE(list.size() == 0);
        REQUIRE(list.isEmpty());
        REQUIRE(list.elementAt(0) == nullptr);
    }
}

TEST_CASE("LinkedList.insertFront", "[LinkedList][insertFront]") {
    LinkedList list;

    Kebab *item1 = new Kebab();
    item1->addIngredient('b');
    item1->addIngredient('p');
    item1->addIngredient('m');

    Kebab *item2 = new Kebab();
    item2->addIngredient('m');
    item2->addIngredient('m');
    item2->addIngredient('m');

    SECTION("inserts into an empty list") {
        list.insertFront(item1);
        
        REQUIRE(list.size() == 1);
        REQUIRE(list.elementAt(0) == item1);
    }

    SECTION("inserts into the front of the list") {
        list.insertFront(item1);
        list.insertFront(item2);

        REQUIRE(list.size() == 2);
        REQUIRE(list.elementAt(0) == item2);
        REQUIRE(list.elementAt(1) == item1);
    }
}

TEST_CASE("LinkedList.insertBack", "[LinkedList][insertBack]") {
    LinkedList list;
    
    Kebab *item1 = new Kebab();
    item1->addIngredient('b');
    item1->addIngredient('p');
    item1->addIngredient('m');

    Kebab *item2 = new Kebab();
    item2->addIngredient('m');
    item2->addIngredient('m');
    item2->addIngredient('m');

    SECTION("inserts into an empty list") {
        list.insertBack(item1);
        
        REQUIRE(list.size() == 1);
        REQUIRE(list.elementAt(0) == item1);
    }

    SECTION("inserts into the back of the list") {
        list.insertBack(item1);
        list.insertBack(item2);

        REQUIRE(list.size() == 2);
        REQUIRE(list.elementAt(0) == item1);
        REQUIRE(list.elementAt(1) == item2);
    }
}

TEST_CASE("LinkedList.contains", "[LinkedList][contains]") {
    LinkedList list;
    
    Kebab *item1 = new Kebab();
    item1->addIngredient('b');
    item1->addIngredient('p');
    item1->addIngredient('m');

    Kebab *item2 = new Kebab();
    item2->addIngredient('m');
    item2->addIngredient('m');
    item2->addIngredient('m');

    Kebab *item3 = new Kebab();
    item3->addIngredient('p');
    item3->addIngredient('m');
    item3->addIngredient('b');

    Kebab *item4 = new Kebab();
    item4->addIngredient('s');
    item4->addIngredient('s');
    item4->addIngredient('s');

    list.insertFront(item1);
    list.insertFront(item2);

    SECTION("finds matching kebabs") {
        REQUIRE(list.contains(*item1));
    }

    SECTION("finds matching kebabs with ingredients in a different order") {
        REQUIRE(list.contains(*item3));
    }

    SECTION("produces false for non-matching kebabs") {
        REQUIRE_FALSE(list.contains(*item4));
    }
}
    
// Grill test cases need to be careful with the ingredients
//   since we can't guarantee the order of items in student submissions

TEST_CASE("Grill", "[Grill]") {
  Grill g;
  std::vector<std::string> kebabs;

  SECTION("no kebabs on a new empty grill") {
    kebabs = g.showKebabs();
    REQUIRE(kebabs.size() == 0);
  }
}

TEST_CASE("Grill.addKebab", "[Grill][addKebab]") {
  Grill g;
  std::vector<std::string> kebabs;

  Kebab* k1 = new Kebab(); // bbb
  Kebab* k2 = new Kebab(); // (empty)
  Kebab* k3 = new Kebab(); // sss

  k1->addIngredient('b');  k1->addIngredient('b');  k1->addIngredient('b');
  k3->addIngredient('s');  k3->addIngredient('s');  k3->addIngredient('s');

  SECTION("kebabs added in order of input") {
    g.addKebab(*k1);
    g.addKebab(*k2);
    g.addKebab(*k3);
    kebabs = g.showKebabs();
    REQUIRE(kebabs[0] == "bbb");
    REQUIRE(kebabs[1] == "");
    REQUIRE(kebabs[2] == "sss");
  }
}

TEST_CASE("Grill.swap", "[Grill][swap]") {
  Grill g;
  std::vector<std::string> kebabs;

  Kebab* k1 = new Kebab(); // bbb
  Kebab* k2 = new Kebab(); // (empty)
  Kebab* k3 = new Kebab(); // sss

  k1->addIngredient('b');  k1->addIngredient('b');  k1->addIngredient('b');
  k3->addIngredient('s');  k3->addIngredient('s');  k3->addIngredient('s');
  
  g.addKebab(*k1);
  g.addKebab(*k2);
  g.addKebab(*k3);

  SECTION("swap with invalid indices should be NOOP") {
    REQUIRE_FALSE(g.swap(1, 100));
    kebabs = g.showKebabs();
    REQUIRE(kebabs[0] == "bbb");
    REQUIRE(kebabs[1] == "");
    REQUIRE(kebabs[2] == "sss");
  }

  SECTION("swap with same index should be NOOP") {
    REQUIRE_FALSE(g.swap(2, 2));
    kebabs = g.showKebabs();
    REQUIRE(kebabs[0] == "bbb");
    REQUIRE(kebabs[1] == "");
    REQUIRE(kebabs[2] == "sss");
  }

  SECTION("swap with valid indices, pos1 < pos2") {
    REQUIRE(g.swap(2, 3));
    kebabs = g.showKebabs();
    REQUIRE(kebabs[0] == "bbb");
    REQUIRE(kebabs[1] == "sss");
    REQUIRE(kebabs[2] == "");

    REQUIRE(g.swap(1, 3));
    kebabs = g.showKebabs();
    REQUIRE(kebabs[0] == "");
    REQUIRE(kebabs[1] == "sss");
    REQUIRE(kebabs[2] == "bbb");

    REQUIRE(g.swap(1, 2));
    kebabs = g.showKebabs();
    REQUIRE(kebabs[0] == "sss");
    REQUIRE(kebabs[1] == "");
    REQUIRE(kebabs[2] == "bbb");
  }

  SECTION("swap with valid indices, pos1 > pos2") {
    REQUIRE(g.swap(3, 2));
    kebabs = g.showKebabs();
    REQUIRE(kebabs[0] == "bbb");
    REQUIRE(kebabs[1] == "sss");
    REQUIRE(kebabs[2] == "");

    REQUIRE(g.swap(3, 1));
    kebabs = g.showKebabs();
    REQUIRE(kebabs[0] == "");
    REQUIRE(kebabs[1] == "sss");
    REQUIRE(kebabs[2] == "bbb");

    REQUIRE(g.swap(2, 1));
    kebabs = g.showKebabs();
    REQUIRE(kebabs[0] == "sss");
    REQUIRE(kebabs[1] == "");
    REQUIRE(kebabs[2] == "bbb");
  }
}

TEST_CASE("Grill.request invalid cases", "[Grill][request]") {
  Grill g;
  std::vector<std::string> kebabs;
  Kebab* requested;

  Kebab* k1 = new Kebab(); // bbb
  Kebab* k2 = new Kebab(); // (empty)
  Kebab* k3 = new Kebab(); // sss

  k1->addIngredient('b');  k1->addIngredient('b');  k1->addIngredient('b');
  k3->addIngredient('s');  k3->addIngredient('s');  k3->addIngredient('s');

  g.addKebab(*k1);
  g.addKebab(*k2);
  g.addKebab(*k3);

  SECTION("requesting invalid position should be NOOP") {
    requested = g.request(100);
    kebabs = g.showKebabs();
    REQUIRE(requested == NULL);
    REQUIRE(kebabs.size() == 3);
    REQUIRE(kebabs[0] == "bbb");
    REQUIRE(kebabs[1] == "");
    REQUIRE(kebabs[2] == "sss");
  }

  SECTION("requesting valid position retains access to kebab and removes from grill") {
    requested = g.request(2);
    kebabs = g.showKebabs();
    REQUIRE(requested == k2);
    REQUIRE(kebabs.size() == 2);
    REQUIRE(kebabs[0] == "bbb");
    REQUIRE(kebabs[1] == "sss");
  }
}

TEST_CASE("Grill.request", "[Grill][request]") {
  Grill g;
  std::vector<std::string> kebabs;
  Kebab* requested;

  Kebab* k1 = new Kebab(); // bbb
  Kebab* k2 = new Kebab(); // (empty)
  Kebab* k3 = new Kebab(); // sss
  Kebab* k4 = new Kebab(); // ss

  k1->addIngredient('b');  k1->addIngredient('b');  k1->addIngredient('b');
  k3->addIngredient('s');  k3->addIngredient('s');  k3->addIngredient('s');
  k4->addIngredient('s');  k4->addIngredient('s');

  g.addKebab(*k1);
  g.addKebab(*k2);
  g.addKebab(*k3);
  g.addKebab(*k4);

  SECTION("requesting kebab with no match should be NOOP") {
    Kebab refk;
    refk.buildKebab("mmmmm");
    requested = g.request(refk);
    kebabs = g.showKebabs();
    REQUIRE(requested == NULL);
    REQUIRE(kebabs.size() == 4);
    REQUIRE(kebabs[0] == "bbb");
    REQUIRE(kebabs[1] == "");
    REQUIRE(kebabs[2] == "sss");
    REQUIRE(kebabs[3] == "ss");
  }

  SECTION("requesting empty ingredient returns the first kebab") {
    Kebab refk;
    requested = g.request(refk);
    kebabs = g.showKebabs();
    REQUIRE(requested == k1);
    REQUIRE(kebabs.size() == 3);
    REQUIRE(kebabs[0] == "");
    REQUIRE(kebabs[1] == "sss");
    REQUIRE(kebabs[2] == "ss");
  }

  SECTION("requesting matching ingredient returns the first match") {
    Kebab refk;
    refk.addIngredient('s');
    requested = g.request(refk);
    kebabs = g.showKebabs();
    REQUIRE(requested == k3);
    REQUIRE(kebabs.size() == 3);
    REQUIRE(kebabs[0] == "bbb");
    REQUIRE(kebabs[1] == "");
    REQUIRE(kebabs[2] == "ss");
  }
}

// will only test with distinct meat numbers, and only meat ingredients
//   in case of students not preserving ingredient order
// not concerned with whether duplicate meat numbers get swapped
TEST_CASE("Grill.sortByMeat", "[Grill][sortByMeat]") {
  Grill g;
  std::vector<std::string> kebabs;

  Kebab* k0 = new Kebab();
  Kebab* k1 = new Kebab();
  Kebab* k2 = new Kebab();
  Kebab* k3 = new Kebab();
  Kebab* k4 = new Kebab();
  Kebab* k5 = new Kebab();
  Kebab* k6 = new Kebab();
  Kebab* k7 = new Kebab();
  Kebab* k8 = new Kebab();

  k0->addIngredient('t');
  k1->addIngredient('b');
  k2->addIngredient('b');  k2->addIngredient('b');
  k3->addIngredient('b');  k3->addIngredient('b');  k3->addIngredient('b');
  k4->addIngredient('b');  k4->addIngredient('b');
  k4->addIngredient('b');  k4->addIngredient('b');
  k5->addIngredient('b');  k5->addIngredient('b');  k5->addIngredient('b');
  k5->addIngredient('b');  k5->addIngredient('b');
  k6->addIngredient('b');  k6->addIngredient('b');  k6->addIngredient('b');
  k6->addIngredient('b');  k6->addIngredient('b');  k6->addIngredient('b');
  k7->addIngredient('b');  k7->addIngredient('b');  k7->addIngredient('b');
  k7->addIngredient('b');  k7->addIngredient('b');  k7->addIngredient('b');
  k7->addIngredient('b');
  k8->addIngredient('b');  k8->addIngredient('b');  k8->addIngredient('b');
  k8->addIngredient('b');  k8->addIngredient('b');  k8->addIngredient('b');
  k8->addIngredient('b');  k8->addIngredient('b');

  SECTION("sorts a grill starting in ascending order") {
    g.addKebab(*k0);  g.addKebab(*k1);  g.addKebab(*k2);  g.addKebab(*k3);
    g.addKebab(*k4);  g.addKebab(*k5);  g.addKebab(*k6);  g.addKebab(*k7);
    g.addKebab(*k8);
    g.sortByMeat();

    kebabs = g.showKebabs();
    REQUIRE(kebabs.size() == 9);
    REQUIRE(kebabs[0] == "bbbbbbbb");
    REQUIRE(kebabs[1] == "bbbbbbb");
    REQUIRE(kebabs[2] == "bbbbbb");
    REQUIRE(kebabs[3] == "bbbbb");
    REQUIRE(kebabs[4] == "bbbb");
    REQUIRE(kebabs[5] == "bbb");
    REQUIRE(kebabs[6] == "bb");
    REQUIRE(kebabs[7] == "b");
    REQUIRE(kebabs[8] == "t");
  }

  SECTION("sorts a grill starting in descending order") {
    g.addKebab(*k8);  g.addKebab(*k7);  g.addKebab(*k6);  g.addKebab(*k5);
    g.addKebab(*k4);  g.addKebab(*k3);  g.addKebab(*k2);  g.addKebab(*k1);
    g.addKebab(*k0);
    g.sortByMeat();

    kebabs = g.showKebabs();
    REQUIRE(kebabs.size() == 9);
    REQUIRE(kebabs[0] == "bbbbbbbb");
    REQUIRE(kebabs[1] == "bbbbbbb");
    REQUIRE(kebabs[2] == "bbbbbb");
    REQUIRE(kebabs[3] == "bbbbb");
    REQUIRE(kebabs[4] == "bbbb");
    REQUIRE(kebabs[5] == "bbb");
    REQUIRE(kebabs[6] == "bb");
    REQUIRE(kebabs[7] == "b");
    REQUIRE(kebabs[8] == "t");
  }

  SECTION("sorts a grill starting in arbitrary order") {
    g.addKebab(*k4);  g.addKebab(*k8);  g.addKebab(*k1);  g.addKebab(*k7);
    g.addKebab(*k2);  g.addKebab(*k5);  g.addKebab(*k6);  g.addKebab(*k0);
    g.addKebab(*k3);
    g.sortByMeat();

    kebabs = g.showKebabs();
    REQUIRE(kebabs.size() == 9);
    REQUIRE(kebabs[0] == "bbbbbbbb");
    REQUIRE(kebabs[1] == "bbbbbbb");
    REQUIRE(kebabs[2] == "bbbbbb");
    REQUIRE(kebabs[3] == "bbbbb");
    REQUIRE(kebabs[4] == "bbbb");
    REQUIRE(kebabs[5] == "bbb");
    REQUIRE(kebabs[6] == "bb");
    REQUIRE(kebabs[7] == "b");
    REQUIRE(kebabs[8] == "t");
  }
}
