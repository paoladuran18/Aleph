
# include <autosprintf.h>
# include <limits>
# include <sstream>

using format = gnu::autosprintf;

using Grid = DynMatrix<char>;

using Trace = DynMatrix<bool>;

using Cell = tuple<int, int>;


inline string to_str(const Grid & grid)
{
  int col_width = to_str(grid.cols() - 1).size();
  int row_width = to_str(grid.rows() - 1).size();

  string ret = string(row_width, ' ') +
    range<int>(0, grid.cols() - 1).foldl<string>("", [col_width] (const string & s, const int & i)
    {
      string str = to_str(i);
      return s + string(col_width - str.size() + 1, ' ') + str + " ";
    }) + "\n";

  for (int i = 0; i < grid.rows(); ++i)
    {
      ret += string(row_width - to_str(i).size(), ' ') + to_str(i);
      for (int j = 0; j < grid.cols(); ++j)
	{
	  ret += string(col_width, ' ');
	  ret.push_back(grid(i, j));
	  ret.push_back(' ');
	}
      ret.push_back('\n');
    }
  return move(ret);
}

inline ostream & operator << (ostream & s, const Grid & grid)
{
  return s << to_str(grid);
}


inline Grid load_grid(istream & in)
{
  string line;
  int ncol;

  {
    getline(in, line);    // leer indices de columnas
    stringstream ss(line);
    for (int prev = -1; ss >> ncol; prev = ncol)
      if (ncol != prev + 1)
	throw domain_error("invalid column number");
    ++ncol;
  }

  DynList<DynList<char>> rows;
  int nrow;
  for (int prev = -1; in; prev = nrow)
    {
      getline(in, line);
      stringstream ss(line);

      ss >> nrow; // lee número de fila
      if (not in)
	break;

      if (nrow != prev + 1)
	throw domain_error("invalid row number");
      
      char c;
      DynList<char> row;

      while (ss >> c) // leer resto de la línea
	row.append(c);
      
      if (row.size() != ncol)
	throw domain_error(format("read cols (%d) mismatch with header "
				  "spec (%d)", row.size(), ncol));

      rows.append(move(row));
    }

  Grid grid(++nrow, ncol); grid.allocate();

  int i = 0;
  rows.for_each([&i, &grid] (const DynList<char> & row)
    {
      int j = 0;
      row.for_each([i, &j, &grid] (char c) { grid(i, j++) = c; });
      ++i;
    });

  return move(grid); 
}

