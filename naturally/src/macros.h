// NOTE: I this is meant to be included more than once.
#define FILE_META __FILE__ + ":" __LINE__

// What I REALLY want is a system for exploring properties of the natural
// numbers.
//
// Then I need a database.
// I need it to be designed s.t. I can move from sqlite to redis to mongo to
// postgres without clients noticing.
//
// then I need a way to serialize this stuff...
// consider again encoding properties as enums to be logically added/parsed
// from a single integer representing n's
