#pragma once

// NOTE: what i really want
// is a way to know what to do.
// and to know what's true.
// algorithms
// throerem provers
// they're the things to do.
// merely skimped over algorithms.
// they are not your destiny.
// yes, you were the kid watching several games
// of other children bowling before understanding
// obtaining enough procedural knowledge to feel confident
// enough to play.
// say, what do you think you'll purchase today?
// stay.

#include <string>
#include <vector>
namespace PredicateCalculus {

/*
   I want to say
   let p1("Donald Trump was the 69th president.");
   let p2("The 69th president had herpes.");
   let p3("Donald Trump had herpes.");

   // from below:
   // that's a lot of work.
   // what i really want to say is
   Prove([p1,p2], p3);
   // that's what I really want.

   // start simply.
   // if the system has no notion of the past...
   let p1(['is 69th president', 'is DT'])
   let p2(['is 69th president', 'is positive for herpes simplex b.'])
   let p3(['is DT', 'is herp+'])
   Prove([p1,p2], )


   // but what does p1 'say'?
   // There exists some x s.t. x is named DT ^ x was the 69th prez.
   // what does p2 say?
   // there exists some y s.t. y was the 69th prez ^ y had herp.
   // if a variable is classless
   // we can assume uniform class across members
   // of the set of propositions introduced into our proof space.
   // or something fancy like that.

   ...
   how do we invite/allow/accept an axiom for use in the system?
   e.g. we'd be citing our steps somehow...making explicit
   things mathematicians leave implicit leaving us staring
   at glyphs for ages comprehending little.
   allow(Axiom::LogicalSyllogism);
   by(Axiom::LogicalSyllogism);
   deduction = deduce();
   syllogise(p1,p2);
   ...

   -> "Donald Trump had herpes."
 */

class Statement {
public:
  Statement(std::string s) : _s(s) {}

protected:
  std::string _s;
};

class Proposition : Statement {
protected:
  bool is_true = true;
};

// a proposition is a statement that is either true or false.
// a predicate is a proposition whose truth depends on the value of a variable.
// a compound proposition e.g. p1 AND p2; !p1 etc.
// an axiom is a proposition that is assumed to be true.
// e.g. T -> A0
// axioms should be
//   - consistent
//     a set of axioms is consistent if no proposition can be proved to be both
//     true and false.
//   - complete
//     a set of axioms is complete if it can be used to prove every proposition
//     is either true or false.
// e.g. godel's incompleteness thm demonstrated
// the impossibility of the existence of any set of axioms which are both
// consistent and complete.
// ...if you want consistency (a must) you sacrifice completeness. e.g.
// there will be true facts unprovable w/in the system.

class let {
public:
  let() {}
  // TODO: actually concern ourselves
  // with the type of stmt. string(proposition),
  // "variable binding" etc.
  let(std::vector<std::string> given_properties)
      : _given_properties(given_properties) {}

protected:
  std::vector<std::string> _given_properties;
};

enum class Qualifier { EX, AX };

//   stmt s1(EX, "is DT.")
class Stmt {
public:
  Stmt() : _qualifier(Qualifier::EX), _predicate("") {}
  Stmt(Qualifier ue, std::string p) : _qualifier(ue), _predicate(p) {}

protected:
  Qualifier _qualifier;
  std::string _predicate;
};

enum class Operator { Conjunction, Disjunction };

class CompoundStmt {
public:
  CompoundStmt(Stmt lhs, Stmt rhs, Operator op)
      : _lhs(lhs), _rhs(rhs), _op(op) {}

protected:
  Stmt _lhs;
  Stmt _rhs;
  Operator _op;
};

class Prove {
public:
  static bool It() { return true; }
};

// {
//   let p1([ "is DT", "is 69th president" ]);
//   let p2([ "is 69th president", "herp+" ]);
//   let p3([ "is DT", "herp+" ]);
//   bool dt_has_herp_p = Prove::It([ p1, p2 ], p3);
//   if (dt_has_herp_p) {
//     std::cout << "its true." << std::endl;
//   }
//
// HERE:
//   ...nope. i'm skipping steps...
//   //let p1(X, "is 69th president");
//   let p1("is 69th president");
//   //let p2(X, "is DT");
//   let p2("is DT");
//   let p3("herp+");
//   //var x();
//   //maybe X could be an enum...why not?
//   stmt s1(EXISTS, X, [p1, p2]);
//   stmt s2(EXISTS, X, [p2, p3]);
//   stmt s3(EXISTS, X, [p1, p3]);
//   bool dt_has_herpe = ItFollowsThat([s1, s2], s3);
//   //...nah.. we're anding things. we ought to explicate it.
//   // it's looking like Ss and Ps are the same thing.
//   // we merely need a notion of conjunction of statements.
//   maybe can say
//   stmt s1(THERE_EXISTS_SOME_X, "is DT.")
//   stmt s1(THERE_EXISTS_SOME_X, "is DT.")
//   stmt s1(EX_X, "is DT.")
//   stmt s1(EX, "is DT.")
//   // later?
//   stmt sn(EY, "is DT.")
//   stmt s1(EXISTS, X, "is DT.")
//   stmt s2(EXISTS, X, "is 69th pres.")
//   stmt s3(EXISTS, X, "herp+")
//   // perhaps conjoin returns a stmt built from two...
//   sounds like what it do.
//   stmt s4(s1.conjoin(s2));
//   stmt s5(s2.conjoin(s3));
//   stmt s6(s1.conjoin(s3));
//   bool dt_have_herpee = Prove::ItFollowsThat([s4,s5],s6);
//   getting closer.
//
//
//
// }

enum class StatementSource { Given, Deduced };

// class Statement {
// public:
//   Statement() : _source(StatementSource::Given) {}
//   Statement(std::string eng) : _english(eng), _source(StatementSource::Given)
//   {}
//
// protected:
//   StatementSource _source;
//   std::string _english;
// };

// TODO:
// so a variable holds a statement
// yet a statement may be about a variable...hmmm.
// ...think more carefully.
// class Variable {
// public:
//   // Variable() {}
//   Variable(Statement s, std::string n) : _statement(s), _name(n) {}
//
// protected:
//   Statement _statement;
//   std::string _name;
// };

} // namespace PredicateCalculus
