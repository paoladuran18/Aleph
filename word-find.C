
# include <istream>

# include <ahSort.H>
# include <tpl_dynMat.H>
# include <tpl_tree_node.H>
# include <generate_tree.H>

# include <dictnode.H>

# include <grid.H>
# include <word-find.H>

void usage()
{
  cout << "usage" << endl
       << "    word-find word-find-file" << endl;
  exit(0);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    usage();

  ifstream word_find(argv[1]);
  if (not word_find.is_open())
    {
      cout << "cannot open file " << argv[1] << endl;
      exit(0);
    }
cout << "holaaaaaaaaaaaaaaa";
  Grid grid = load_grid(word_find);
  cout << grid << endl;
  WordFind(grid).solve(cin).for_each([] (const WordMove & t)
    {
      cout << get<0>(t) << " ";
      get<1>(t).for_each([] (const Cell & c)
			 {
			   cout << "(" << get<0>(c) << "," << get<1>(c) << ")";
			 });
      cout << endl;
    });
  auto l = legal_moves(1,1);
  for(auto &i : l)
    cout << get<0>(i) << "," << get<1>(i) << " ";
  
  return 0;
}
