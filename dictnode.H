
# include <tpl_arrayStack.H>
# include <tpl_tree_node.H>

using namespace std;

class Cnode : public Tree_Node<char>
{
  static char filter_char(register const char);
  static char fast_filter_char(register const char);
  static string filter_string(const string &);
  static char * filter_string(char *);

public:

  Cnode(const char);

  char symbol();

  DynList<Cnode*> children();

  string to_str();

private:
  struct W
  {
    const string operator () (Cnode * p) const;
  };

public:

  void ntreepic(ostream &);

  bool is_end_word();

  void mark_end_word();

  Cnode * search_child(const char);

private:

  Cnode * greater_child(const char);

public:

  tuple<Cnode*, const char*> search_prefix(const char *);

  Cnode * search_word(const char *);

  bool contains(const string &);

  Cnode * insert_child(Cnode *);

  bool insert_word(const string &);

  void destroy();

private:

  string extract_word_from_stack(FixedStack<char> &);
  void words(FixedStack<char> &, DynArray<string> &);

public:

  DynArray<string> words();

  void print_words();
};

