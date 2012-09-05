#include "gtest/gtest.h"
#include <string>
#include <iostream>

using namespace std;

// CODE UNDER TEST
const string SPACE = " ";
const string TAB = "\t";
const string NEWLINE = "\n";
const string CARRAIGE_RETURN = "\r";
const string VERTICAL_TAB = "\v";
const string BACKSPACE = "\b";
const string FORM_FEED = "\f";

const string WHITESPACE = SPACE + TAB + NEWLINE + CARRAIGE_RETURN + VERTICAL_TAB + BACKSPACE + FORM_FEED;

string reverseCharacters(string input, int stIdx, int edIdx)
{
  int len = edIdx - stIdx + 1;
    if ( 1 >= len )
    {
      string tail = input.substr(stIdx, len);
      return tail;
    }
  string firstChar = input.substr(edIdx, 1);
  string remainingChars = reverseCharacters( input, stIdx, edIdx - 1);
  return firstChar + remainingChars;
}

string reverseWords(string input)
{
  string accumulator("");
  
  int initialIdx = 0;
  int spaceIdx = input.find_first_of(WHITESPACE, initialIdx);
  string substr = input.substr(initialIdx, spaceIdx - initialIdx);
  accumulator.append(reverseCharacters(input, initialIdx, (-1 == spaceIdx) ? input.length() - 1: spaceIdx - 1));

  if ( -1 != spaceIdx )
    {
      accumulator.append(input.substr(spaceIdx,1));
      accumulator.append(reverseWords(input.substr(spaceIdx - initialIdx + 1)));
    }
  
  return accumulator;
}

string reverse(string input)
{
  return reverseWords(reverseCharacters(input, 0, input.length() -1 ));
}

// TESTS
TEST(CharacterReverser, ReversesGivenStringWithIndexes)
{
  ASSERT_EQ("cba", reverseCharacters("abc", 0, 2));
}

TEST(CharacterReverser, FourCharReversesGivenStringWithIndexes)
{
  ASSERT_EQ("dcba", reverseCharacters("abcd", 0, 3));
}

TEST(CharacterReverser, TwoCharWithSpaceReversesGivenStringWithIndexes)
{
  ASSERT_EQ("d a", reverseCharacters("a d", 0, 2));
}

TEST(CharacterReverser, FourCharWithSpacesReversesGivenStringWithIndexes)
{
  ASSERT_EQ("d c b a", reverseCharacters("a b c d", 0, 6));
}

TEST(CharacterReverser, WorksOnAPartial) 
{
  ASSERT_EQ("defg", reverseCharacters("abcgfed",3, 6));
}


TEST(CharacterReverser, SingleCharReversesGivenStringWithIndexes)
{
  ASSERT_EQ("a", reverseCharacters("a", 0, 1));
}

TEST(StringReverser, IsIdentityOperationOverEmptyString) 
{
  ASSERT_EQ("", reverse("")) << "Empty string is not empty";
}

TEST(StringReverser, IsIdentityOperationOverSingleCharacter)
{
  ASSERT_EQ("a", reverse("a")) << "Single Character string is not identity";
}

TEST(StringReverser, ReversesCharactersSeperatedByWhiteSpace)
{
  ASSERT_EQ("j i", reverse("i j")) << "Single Character Words not reversed";
}

TEST(StringReverser, ReversesCharacterPairsSeperatedByWhiteSpace)
{
  ASSERT_EQ("kl ij", reverse("ij kl")) << "Multicharacter Pairs Not Reversed";
}

TEST(TripleWordStringReverser, PutsLastWordFirstAndFirstWordLast)
{
  ASSERT_EQ("klmnop defghij abc", reverse("abc defghij klmnop")) << "First word is not last, or last word is not first. Or both.";
}

TEST(StringReverser, AdjacentSpacesPreservedInOutput) 
{
  ASSERT_EQ("xyzzy  lmnop", reverse("lmnop  xyzzy")) << "Adjacent Spaces should be preserved in output";
}

TEST(StringReverser, LeadingSpaceBecomesTrailingSpace)
{
  ASSERT_EQ("world hello ", reverse(" hello world")) << "Leading space should become trailing space";
}

TEST(StringReverser, TrailingSpaceBecomesLeadingSpace)
{
  ASSERT_EQ("  hello world", reverse("world hello  ")) << "Trailing space should become leading space";
}

TEST(StringReverser, IsIdentityOperationOverMulticharacterWord)
{
  ASSERT_EQ("xyzzy", reverse("xyzzy")) << "Multicharacter word is not identity";
}

TEST(StringReverser, TabIsWhitespaceToo)
{
  ASSERT_EQ("world\thello", reverse("hello\tworld")) << "Tabs should be treated like a whilspace";
}

TEST(StringReverser, NewlineIsWhitespaceToo)
{
  ASSERT_EQ("world\nhello", reverse("hello\nworld")) << "Newline should be treated like a whilspace";
}

TEST(StringReverser, CarriageReturnIsWhitespaceToo)
{
  ASSERT_EQ("world\rhello", reverse("hello\rworld")) << "Carriage Return should be treated like a whilspace";
}

TEST(StringReverser, VerticalTabIsWhitespaceToo)
{
  ASSERT_EQ("world\vhello", reverse("hello\vworld")) << "Vertical Tab should be treated like a whilspace";
}

TEST(StringReverser, BackspaceIsWhitespaceToo)
{
  ASSERT_EQ("world\bhello", reverse("hello\bworld")) << "Backspace should be treated like a whilspace";
}

TEST(StringReverser, FormFeedIsWhitespaceToo)
{
  ASSERT_EQ("world\fhello", reverse("hello\fworld")) << "Form Feed should be treated like a whilspace";
}

TEST(StringReverser, MultipleWhitespaceIsReversedWhitespace)
{
  ASSERT_EQ(" \b\v\r\b\n\f\t ", reverse(" \t\f\n\b\r\v\b ")) << "Whitespaces were not reveresed";
}

