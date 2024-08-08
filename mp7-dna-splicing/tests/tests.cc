#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include "dna_strand.hpp"

/*
TEST_CASE("Example 1 Object Creation", "[ex_1_obj]") { 
    
    Node* t8 = new Node('g');
    Node* t7 = new Node('c', t8);
    Node* t6 = new Node('t', t7);
    Node* t5 = new Node('t', t6);
    Node* t4 = new Node('a', t5);
    Node* t3 = new Node('a', t4);
    Node* t2 = new Node('g', t3);
    Node* t1 = new Node('t', t2);
    Node* t0 = new Node('c', t1);

    DNAstrand t;

    t.SetHead(t0);
    t.SetTail(t8);

    // char pattern1[] = "gaattc";

    DNAstrand sp;

    Node* s4 = new Node('c');
    Node* s3 = new Node('t', s4);
    Node* s2 = new Node('a', s3);
    Node* s1 = new Node('g', s2);
    Node* s0 = new Node('t', s1);

    sp.SetHead(s0);
    sp.SetTail(s4);

    //t.SpliceIn(pattern1, sp);

    //t.DisplayList();

    //sp.DisplayList();

    REQUIRE(true == true); 
}


TEST_CASE("ListToString", "[list_to_string]") { 
    
    Node* t8 = new Node('g');
    Node* t7 = new Node('c', t8);
    Node* t6 = new Node('t', t7);
    Node* t5 = new Node('t', t6);
    Node* t4 = new Node('a', t5);
    Node* t3 = new Node('a', t4);
    Node* t2 = new Node('g', t3);
    Node* t1 = new Node('t', t2);
    Node* t0 = new Node('c', t1);

    DNAstrand t;

    t.SetHead(t0);
    t.SetTail(t8);

    Node* s4 = new Node('c');
    Node* s3 = new Node('t', s4);
    Node* s2 = new Node('a', s3);
    Node* s1 = new Node('g', s2);
    Node* s0 = new Node('t', s1);

    DNAstrand sp;
    sp.SetHead(s0);
    sp.SetTail(s4);

    //char p[] = "gaattc";

    //unsigned int pattern_sz = t.StrLen(p);
    //std::cout << "Length of pattern: " << pattern_sz << std::endl;

    //const char* x1 = t.ListToString();
    //const char* x2 = sp.ListToString();

    //std::cout << "Length of x1: " << t.StrLen(x1) << std::endl;
    //std::cout << "Length of x2: " << t.StrLen(x2) << std::endl;

    //t.DisplayCString(x1);
    //sp.DisplayCString(x2);

    REQUIRE(true == true); 
}


TEST_CASE("Pattern longer than list", "[pattern_too_long]") { 
    
    Node* t8 = new Node('g');
    Node* t7 = new Node('c', t8);
    Node* t6 = new Node('t', t7);
    Node* t5 = new Node('t', t6);
    Node* t4 = new Node('a', t5);

    DNAstrand t;

    t.SetHead(t4);
    t.SetTail(t8);

    char p[] = "gaattc";

    REQUIRE_THROWS(t.MatchingIndex(p));
}

TEST_CASE("Pattern not found", "[pattern_not_found]") { 
    
    Node* t8 = new Node('g');
    Node* t7 = new Node('c', t8);
    Node* t6 = new Node('t', t7);
    Node* t5 = new Node('t', t6);
    Node* t4 = new Node('a', t5);
    Node* t3 = new Node('a', t4);
    Node* t2 = new Node('g', t3);
    Node* t1 = new Node('t', t2);
    Node* t0 = new Node('c', t1);

    DNAstrand t;

    t.SetHead(t0);
    t.SetTail(t8);

    char p[] = "gaxttc";

    REQUIRE_THROWS(t.MatchingIndex(p));
}

TEST_CASE("Matching Index", "[matching_index_test]") { 
    
    Node* t8 = new Node('g');
    Node* t7 = new Node('c', t8);
    Node* t6 = new Node('t', t7);
    Node* t5 = new Node('t', t6);
    Node* t4 = new Node('a', t5);
    Node* t3 = new Node('a', t4);
    Node* t2 = new Node('g', t3);
    Node* t1 = new Node('t', t2);
    Node* t0 = new Node('c', t1);

    DNAstrand t;

    t.SetHead(t0);
    t.SetTail(t8);

    char p[] = "gaattc";

    DNAstrand sp;

    Node* s4 = new Node('c');
    Node* s3 = new Node('t', s4);
    Node* s2 = new Node('a', s3);
    Node* s1 = new Node('g', s2);
    Node* s0 = new Node('t', s1);

    sp.SetHead(s0);
    sp.SetTail(s4);

    //t.SpliceIn(pattern1, sp);

    REQUIRE(t.MatchingIndex(p) == 2); 
}
*/

TEST_CASE("Splicing Example 1", "[splice_one]") { 
    
    Node* t8 = new Node('g');
    Node* t7 = new Node('c', t8);
    Node* t6 = new Node('t', t7);
    Node* t5 = new Node('t', t6);
    Node* t4 = new Node('a', t5);
    Node* t3 = new Node('a', t4);
    Node* t2 = new Node('g', t3);
    Node* t1 = new Node('t', t2);
    Node* t0 = new Node('c', t1);

    DNAstrand t;

    t.SetHead(t0);
    t.SetTail(t8);

    char p[] = "gaattc";

    DNAstrand sp;

    Node* s4 = new Node('c');
    Node* s3 = new Node('t', s4);
    Node* s2 = new Node('a', s3);
    Node* s1 = new Node('g', s2);
    Node* s0 = new Node('t', s1);

    sp.SetHead(s0);
    sp.SetTail(s4);

    t.SpliceIn(p, sp);
    //t.DisplayList();

    REQUIRE(true == true); 
}


/*
TEST_CASE("Splicing Example 2", "[splice_two]") { 
    
    Node* t4 = new Node('a');
    Node* t3 = new Node('t', t4);
    Node* t2 = new Node('a', t3);
    Node* t1 = new Node('t', t2);
    Node* t0 = new Node('c', t1);

    DNAstrand t;

    t.SetHead(t0);
    t.SetTail(t4);

    //char p[] = "ta";

    DNAstrand sp;

    Node* s2 = new Node('a');
    Node* s1 = new Node('g', s2);
    Node* s0 = new Node('t', s1);

    sp.SetHead(s0);
    sp.SetTail(s2);

    //t.SpliceIn(p, sp);
    //t.DisplayList();

    REQUIRE(true == true); 
}
*/