#include<iostream>
#include<vector>
#include <fstream>
#include<string.h>
#include <ctype.h>
#include <iomanip>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
using namespace std;

int guTestNum = 0;
ifstream ifs;
ofstream ofs;
int line = 0, column = 0, startline = 0;

struct token{
	 string s ;
	 string type ;
	 string errorline;
};

struct tree{
  string str;
  string type;
  tree *d;
  tree *r;
  tree *address;
}; // list data structure

struct def{
  string symbol;
	string type;
  tree *bind;
  tree *addr;
};

tree *eval( tree *root, int level, vector<def> &d, bool & exit ) ;

double Stod( string s ){
  stringstream ss ;
  double val = 0;
  ss << s;
  ss >> val;
  return val;
} // Stod ;


bool isInteger( string& str) {
    if (str.empty()) {
        return false;  // 空字符串不是整?
    }

    std::size_t i = 0;

    if (i < str.length() && (str[i] == '+' || str[i] == '-')) {
        i++;
    } // if

    if (i >= str.length() || !isdigit(str[i])) {
        return false;
    } // if

    while (i < str.length() && isdigit(str[i])) {
        i++;
    } // while

    while (i < str.length() && isspace(str[i])) {
        i++;
    } // while

    return i == str.length();
}

void Add_Fuc( vector<def> &d  ) {
  def temp;
  temp.symbol = "define";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure define>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;
  
  temp.symbol = "exit";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure exit>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;
  
  temp.symbol = "clean-environment";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure clean-environment>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "cons";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure cons>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "cond";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure cond>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "if";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure if>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  

  temp.symbol = "list";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure list>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "car";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure car>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "cdr";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure cdr>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "eqv?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure eqv?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "equal?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure equal?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = ">";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure >>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = ">=";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure >=>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "<";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure <>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "<=";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure <=>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  

  temp.symbol = "quote";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure quote>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "=";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure =>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "string-append";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure string-append>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "string>?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure string>?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "string<?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure string<?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "string=?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure string=?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "string?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure string?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;  
  
  temp.symbol = "null?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure null?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;    
  
  temp.symbol = "boolean?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure boolean?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "pair?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure pair?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   

  temp.symbol = "integer?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure integer?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "real?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure real?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "number?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure number?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "symbol?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure symbol?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "list?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure list?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "+";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure +>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "-";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure ->";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "*";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure *>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "/";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure />";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "not";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure not>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "begin";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure begin>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "atom?";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure atom?>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "and";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure and>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
  
  temp.symbol = "or";
  temp.type = "SYMBOL";
  temp.bind = new tree();
  temp.bind->str = "#<procedure or>";
  temp.addr = temp.bind;
  d.push_back( temp ) ;   
    
} 

bool Isfloat( string line ) {
    bool check = true;
    bool hasnum = false;
    int count = 0;
    if ( isdigit(line[0]) || line[0] == '-' ) { // ?? , -?? 
    	for ( int i = 1; line[i] != '\0' ; i++) {
		    if ( !isdigit( line[i] ) && line[i] != '.' ) 
                check = false ;
        } // for
    }
	else if ( line[0] == '+' ) {
	    if ( isdigit(line[1]) || line[1] == '-' || line[1] == '.' ) { // + , +-?? 
	    	for ( int i = 2; line[i] != '\0' ; i++) {
			    if ( !isdigit( line[i] ) && line[i] != '.' )  
	                check = false ;
	        } // for
        }
        else
          check = false ;
	}
	else if ( line[0] == '.' ) { // .?? 
	    for ( int i = 1; line[i] != '\0' ; i++) {
			if ( !isdigit( line[i] ) ) 
	            check = false ;
	    } // for
	}
	else
	  check = false;
    
    for( int i = 0 ; line[i]!= '\0' ; i++ ){
        if ( line[i] == '.' ) count++ ;
		if ( isdigit(line[i]) )  hasnum = true;	
	}
    if ( hasnum && count <= 1 )  return check ;
    else return false;
} // Isfloat

bool Finddot ( string line ) {
    bool found = false;
    for ( int i = 0; line[i] != '\0' ; i++) {
        if ( line[i] == '.' )
          found = true;
    } //for

    return found;
} // Findot()

void read( vector<string> &input ) {
  for( ; !ifs.eof(); ){
    string tmp;
    getline( ifs, tmp);
    input.push_back( tmp );
  }
}

string change( string old ){
    int del = 0;
    bool no = false;
    string nstr;
    for( int i = 0; i < old.length(); i++ ){
        if( old[i] == '.' ){
            if( isdigit(old[i-1] ) || old[i-1] != ' ' ) {
              nstr.push_back( old[i] );
              //nstr.push_back( old[i+1] );
            }
            else{
              int j = i+1;
              while( isspace( old[j] ) ){
                  j++;
              }
              if( old[j] == '(' ){
                  del++;
                  nstr.push_back( ' ' );
                  i = j;
              }
              else{
                  nstr.push_back( old[i] );
              }              
            }
        }
        else if( old[i] == ')'  ){
            if( del != 0 && no != true  ){
                del--;
            }
            else if( no == true ){
              nstr.push_back( old[i] );
              no = false;
            }
            else{
                nstr.push_back( old[i] );
            }
        }
        else if( del != 0 && old[i] == '(' ){
          no = true ;
          nstr.push_back( old[i] );
        }
        else {
            if( old[i] == '"' ){
              int find = 1;
              while( find != 0 ){
                nstr.push_back( old[i] );
                i++;
                if( old[i] == '"' && old[ i+1 ] == ' ' ){
                  nstr.push_back( old[i] );
                  find = 0;
                }
              }
            }
            else
              nstr.push_back( old[i] );
        }
    }
    return nstr;
}

string del( string old, int del ){
  string nstr;
  for( int i = old.length() -1 ; i >= 0 && del > 0; i--  ){
    if( old[i] == ')' ){
      old.erase( i, 1 );
      del--;
    }
  }
  return old;
}

string Gettype( string s ) {
  if( isInteger(s) )
		return "INTEGER";
	else if ( s[0] == '\"' )
		return "STRING";	
	else if ( s == "t" || s == "#t" )
		return "T";
	else if( Isfloat(s)  )
	  return  "FLOAT";
	else if ( s == "#f" || s == "()" || s == "nil" )
		return "NIL";
	else if ( s == ".")
		return "DOT";
	else if ( s == "(")
		return "LEFT-PAREN";
	else if ( s == ")")
		return "RIGHT-PAREN";
	else 
		return "SYMBOL";
	
} // Gettype()

void create( tree *t, string a, int &i, bool &stop, bool &remain ){
  if( i < a.length() ){
    if( a[i] == '(' ){
      t->str = a[i];
      t->type = Gettype( t->str );
      i++;
      t->d = new tree();
      while( isspace( a[i] ) ){
          i++;
      }
      create( t->d, a, i, stop, remain);
      if( i == a.length() -1 ){
        if( remain == true ){
          remain = false;
          t->r = new tree();
          create( t->r, a, i, stop, remain);
        }  
        stop = true;
      }
      else{
        if( remain == true ){
          remain = false;
          t->r = new tree();
          create( t->r, a, i, stop, remain);
          stop = true;
        }
        else
          stop = false;
      }
    }
    else if( a[i] == ')'  ){

      t->str = a[i];
      t->type = Gettype( t->str );
      if( i == a.length() -1 ){
         //cout << i << endl ;
        stop = true;
      }
	    else{
	      //cout << i << endl;
        i++;
        while( isspace( a[i] ) ){
            i++;
        }
	      if( i == a.length() -1 && a[i] == ')' ){
	        remain = true;
	      }
	          stop = true;
	    }
    }
    else if( a[i] == '.' ){
	      while( !isspace( a[i] ) ){
	        t->str += a[i];
	        i++;
	      }
	      t->type = Gettype( t->str );
        while( isspace( a[i] ) ){
            i++;
        }
        t->r = new tree();
        create( t->r, a, i, stop, remain);
    }
    else  { //push
      if( a[i] == '"' ){
        int find = 1;
        while( find != 0 ){
            t->str += a[i];
            i++;
          if( a[i] == '"' && a[ i +1 ] == ' ' ){
            t->str += a[i];
            find = 0;
            i++;
          }
        }
      }
      while( !isspace( a[i] ) ){
        t->str += a[i];
        i++;
        if ( i == a.length()-1 ) {
        	stop = true;
				} // if
      }

      t->type = Gettype( t->str );
      if ( stop != true ){	
	      while( isspace( a[i] ) ){
	        i++;
	      }
	      t->r = new tree();
	      create( t->r, a, i, stop, remain);
    	} // if 
    }


    if( stop == true )    {
      return;
    }
    else{
      t->r = new tree();
      create( t->r, a, i, stop, remain);
    }         
  }
}

void print(tree *t) {
    if (t == NULL) {
        return ;
    }
    cout << t->str ;
    //cout << "(";
    print(t->d);
    print(t->r);
}

void print(tree *t, int &x, bool &sameline ){
    if (t == NULL) {
        return;
    }
    if( t->str == "(" ){    
      if( x > 0 && sameline != true ){
        for( int i = 0; i < x ; i++ ){
          cout << "  " ;
        }  
      } 
      cout << t->str << " " ;      
      sameline = true;
      x++;
    }
    else if( t->str == ")"){
      x--;
      if( x > 0 ){
        for( int i = 0; i < x ; i++ ){
          cout << "  " ;
        }  
      } 
      
      cout << t->str << endl;
    }
    else{
      if( sameline == true ){
        
        cout << t->str << endl;    
        sameline = false;
      }
      else{
        if( x > 0 ){
          for( int i = 0; i < x ; i++ ){
            cout << "  " ;
          }  
        } 
        
        cout << t->str << endl;             
      }             
    }
    //cout << "(";
    print(t->d, x, sameline);
    print(t->r, x, sameline);
}

void Delnil( vector<token> &tmp){
  for( int i = 0; i < tmp.size(); i++ ){
    if( tmp[i].s == "." ){
      if( tmp[i+1].s == "nil"){
        tmp.erase( tmp.begin()+i, tmp.begin()+i+2  );
      }
    }
  }
}

token gettoken( vector<string> input , int & i , int & j ){ //?n°O±o§P?_???×?????O'(' ???M·|?L?a 
	string s, type, errorline ;
	bool isstring = false ;
	token tk ;
	for( ; j < input[i].size() && isspace(input[i][j]) ; j++);	
  while ( j == input[i].size()  && i+1 < input.size() ){ //????  
    i++;
    for( j = 0 ; isspace(input[i][j]) && j < input[i].size() ; j++);
	}
	
	while (input[i][j] == ';' ){ // comment
		j = input[i].size() ;
		for( ; isspace(input[i][j]) && j < input[i].size() ; j++);	
    while ( j == input[i].size() && i+1 < input.size() ){ //????  
    	i++;
    	for( j = 0 ; isspace(input[i][j]) && j < input[i].size() ; j++);
	  }
	}
		
	if ( input[i][j] == '\"' ) { // string
		s += input[i][j];
		if ( input[i].size()-1 > j ) {
			j++;
			for( ; input[i][j]!='\"' && j < input[i].size() ; j++) {
				if ( input[i][j] == '\\' && input[i].size()-1 > j ){ 
					j++;
      		if ( input[i][j] == 'n' )  
      			s += '\n' ;				
      		else if ( input[i][j] == '\\' )
      			s += '\\' ;					
      		else if ( input[i][j] == 't' )
      			s += '\t' ;		
      		else if ( input[i][j] == '\"' )
      			s += '\"' ;	
      		else
      			s = s + '\\' +  input[i][j];
				}
				else
					s += input[i][j];
			}
		}	
			
	  if ( input[i][j] == '\"'){ //???????? " 
	    isstring = true ;
	    s += input[i][j];
	    j++;
    } 
	}
	else if ( input[i][j] == '(' ) { //(1 2 3 ) 
		s = "("; 
		j++;
	}
	else if ( input[i][j] == ')' ) { //( 1 2 3) 
		s = ")"; 
		j++;
	}
	else if ( input[i][j] == '\'' ) { //quote
		s = "\'"; 
		j++;
	}
	else { //???Ltoken 
		for( ; j < input[i].size() && input[i][j] != '(' && input[i][j] != ')' && input[i][j] != '\"' && input[i][j] != ';' && input[i][j] != '\'' && !isspace(input[i][j]) ; j++) {
		  s += input[i][j];
    } // for
	} // else
//========  tokentype  ==========
	if( Isfloat(s) )
		type = "FLOAT";
	else if ( s[0] == '\"'){
		if( isstring ) 
			type = "STRING";
		else 
			type = "ERROR";	
	}
	else if ( s == "t" || s == "#t" )
		type = "T";
	else if ( s == "#f" || s == "()" || s == "nil" )
		type = "NIL";
	else if ( s == ".")
		type = "DOT";
	else if ( s == "'")
		type = "QUOTE";
	else if ( s == "(")
		type = "LEFT-PAREN";
	else if ( s == ")")
		type = "RIGHT-PAREN";
	else 
		type = "SYMBOL";	
	
	tk.s = s;
	tk.type = type;
	tk.errorline = errorline;
	//cout << tk.s << endl;
	return tk;
}  

void caclulate ( int sel , int i , int j , int linesize , int & eline , int & ecolumn ) {
  if ( sel == 1 ) { // string
	  if ( i == line ) { 
		  eline = 1 ;
		  ecolumn = linesize - column + 1 ;	
	  } // if
	  else {
		  eline = i - line ;
		  ecolumn = linesize + 1 ;
	  } // else
  } // if
  else if ( sel == 2 ) {
	  if ( startline == line ) { // sexp開始那行 
	    if ( i == line ) { // sexp結束那行 
		    eline = 1 ;
		    ecolumn = j - column ;
			} // if 
      else {  // 開始同行 結束不同 
	   	  eline = i - line + 1 ;
		    ecolumn = j ;
			}	 // else 
	  } // if
	  else {
	   	eline = i - line ;
		  ecolumn = j ;
	  } // else
		
  } // else if
	
	
} // caclulate()

void clean( token & tk ) {
  tk.s.clear();
  tk.type.clear();
  tk.errorline.clear();
} // clean

bool Sexp(vector<string> input, vector<token> & list, int & i, int & j, token & tk ){
  clean( tk ) ; 
  int eline = 0, ecolumn = 0;
  bool get = false;
	tk = gettoken( input, i, j);
	if ( list.size() == 0 ) startline = i;
	if ( tk.type == "ERROR" ) {
		caclulate ( 1 , i , j , input[i].size() , eline , ecolumn ) ;
		tk.errorline = "ERROR (no closing quote) : END-OF-LINE encountered at Line " + to_string(eline) + " Column " + to_string(ecolumn);
		return false;
	} // if
	
	if ( tk.type == "SYMBOL" || tk.type == "STRING" || tk.type == "FLOAT"|| tk.type == "NIL" || tk.type == "T" ) {
		list.push_back( tk );
		return true;
	} // if
  else if ( tk.type == "LEFT-PAREN" ) { 
    list.push_back( tk );
    if ( Sexp( input, list, i, j, tk ) ) {
      if ( tk.s == ")") {
      	clean( tk ) ;
      	return true;
	    } // if
    }  // if
    else return false;
	
    while ( Sexp( input, list, i, j, tk ) ) ;
        
		if ( tk.type == "ERROR" ) {
			caclulate ( 1 , i , j , input[i].size() , eline , ecolumn ) ;
			tk.errorline = "ERROR (no closing quote) : END-OF-LINE encountered at Line " + to_string(eline) + " Column " + to_string(ecolumn);
			return false;
		} // if
		
    if ( tk.type == "ERROR2" ) return false;
	
		if ( tk.type == "DOT" ) {
			if ( list[ list.size() - 1 ].s == "(" ) {
		  	caclulate ( 2 , i , j , input[i].size() , eline , ecolumn ) ;
	  		tk.errorline = "ERROR (unexpected token) : atom or '(' expected when token at Line " + to_string(eline) + " Column " + to_string(ecolumn) + " is >>" + tk.s + "<<";
	      return false;				
			} // if
			tk.errorline.clear();
			list.push_back( tk );
			if ( Sexp( input, list, i, j, tk ) )
			  tk = gettoken( input, i, j);
			else 
				return false;
		} // if
		
		if (tk.type == "RIGHT-PAREN" ) {
		  list.push_back( tk );
      clean( tk ) ; 
			return true;
		} // if
		else {
			caclulate ( 2 , i , j , input[i].size() , eline , ecolumn ) ;
			tk.errorline = "ERROR (unexpected token) : ')' expected when token at Line " + to_string(eline) + " Column " + to_string(ecolumn) + " is >>" + tk.s + "<<";
			tk.type = "ERROR2" ;
		  return false;
		} // else
	} 
	else if ( tk.type == "QUOTE" ) {
		tk.s = "(";
		tk.type = "LEFT-PAREN" ;
		list.push_back( tk );
		tk.s = "quote";
		tk.type = "QUOTE" ;  
		list.push_back( tk );
		if ( Sexp( input, list, i, j, tk ) ) {
			tk.s = ")";
			tk.type = "RIGHT-PAREN";
			list.push_back( tk ) ;
			clean(tk);
			return true;
		} // if
		else return false;
	} // else if
	else {
	  if ( tk.s == ")" && list.size() > 0 && list[list.size()-1].s == "("  ){
		  list[list.size()-1].s = "()";
		  list[list.size()-1].type = "NIL";
		  return true;
    }  // if   
	  else {
	  	caclulate ( 2 , i , j , input[i].size() , eline , ecolumn ) ;
  		tk.errorline = "ERROR (unexpected token) : atom or '(' expected when token at Line " + to_string(eline) + " Column " + to_string(ecolumn) + " is >>" + tk.s + "<<";
      return false;
    } // else
	} // else
	
	return true ;
} // Sexp()

void modify( vector<token> & list ) {
  for ( int i = 0 ; i < list.size() ; i++ ){   
  	if ( list[i].s == "t" ) 
  		list[i].s = "#t";
  	else if ( list[i].s == "()" ) 
  		list[i].s = "nil";
  	else if ( list[i].s == "#f" ) 
  		list[i].s = "nil";
  	else if ( Isfloat( list[i].s) ) {       
	    if ( list[i].s[0] == '+' && list[i].s[1] == '-' );
	    else if ( Finddot ( list[i].s ) ){
		    double val = Stod(list[i].s); 
		    stringstream ss;
		    ss << fixed << setprecision(3) << val; 
		    list[i].s = ss.str(); 
		  }
	    else{
		    double val = Stod(list[i].s); 
		    stringstream ss;
		    ss << fixed << setprecision(0) << val; 
		    list[i].s = ss.str();
		  }
	  } 	
  }
} // modify()
 
bool isfuc( string input, int &fuc ){
  if( input == "#<procedure define>" ) {
    fuc = 1;
    return true;
  } // if
  else if( input == "#<procedure exit>" ) {
    fuc = 2;
    return true;
  } // else if
  else if( input == "#<procedure clean-environment>" ) {
    fuc = 3;
    return true;
  } // else if
  else if( input == "#<procedure cons>" ) {
    fuc = 4;
    return true;
  } // else if
  else if( input == "#<procedure cond>" ) {
    fuc = 5;
    return true;
  } // else if
  else if( input == "#<procedure if>" ) {
    fuc = 6;
    return true;
  } // else if
  else if( input == "#<procedure list>" ) return true;
  else if( input == "#<procedure quote>" ) return true;
  else if( input == "#<procedure car>" ) return true;
  else if( input == "#<procedure cdr>" ) return true;
  else if( input == "#<procedure atom?>" ) return true;
  else if( input == "#<procedure pair?>" ) return true;
  else if( input == "#<procedure list?>" ) return true;
  else if( input == "#<procedure null?>" ) return true;
  else if( input == "#<procedure integer?>" ) return true;
  else if( input == "#<procedure real?>" ) return true;
  else if( input == "#<procedure number?>" ) return true;
  else if( input == "#<procedure string?>" ) return true;
  else if( input == "#<procedure boolean?>" ) return true;
  else if( input == "#<procedure symbol?>" ) return true;
  else if( input == "#<procedure +>" ) return true;
  else if( input == "#<procedure ->" ) return true;
  else if( input == "#<procedure *>" ) return true;
  else if( input == "#<procedure />" ) return true;
  else if( input == "#<procedure not>" ) return true;
  else if( input == "#<procedure and>" ) return true;
  else if( input == "#<procedure or>" ) return true;
  else if( input == "#<procedure >>" ) return true;
	else if( input == "#<procedure >=>" ) return true;
  else if( input == "#<procedure <>" ) return true;
  else if( input == "#<procedure <=>" ) return true;
  else if( input == "#<procedure =>" ) return true;
  else if( input == "#<procedure string-append>" ) return true;
  else if( input == "#<procedure string>?>" ) return true;
  else if( input == "#<procedure string<?>" ) return true;
  else if( input == "#<procedure string=?>" ) return true;
  else if( input == "#<procedure eqv?>" ) return true;
  else if( input == "#<procedure equal?>" ) return true;
  else if( input == "#<procedure begin>" ) return true;
  else
    return false;
} // isfuc()
  
bool fuc_arg( string input, int num ){
  input = input.substr( 12 ) ;
  input.erase( input.begin() + input.size() -1  );
  if( input == "define" && num != 2 ) return false ;
  else if( input == "exit" && num != 0 ) return false ;
  else if( input == "clean-environment" && num != 0 ) return false ;
  else if( input == "if" && ( num != 2 && num != 3 ) ) return false ;
  else if( input == "cons" && num != 2 ) return false ;
  else if( input == "cond" && num < 1 ) return false ;
  else if( input == "list" && num < 0 ) return false ;
  else if( input == "quote" && num != 1 ) return false ;
  else if( input == "\'" && num != 1 ) return false ;
  else if( input == "car" && num != 1 ) return false ;
  else if( input == "cdr" && num != 1 ) return false ; 
  else if( input == "atom?" && num != 1 ) return false ; 
  else if( input == "pair?" && num != 1 ) return false ;
  else if( input == "list?" && num != 1 ) return false ;
  else if( input == "null?" && num != 1 ) return false ; 
  else if( input == "integer?" && num != 1 ) return false ;
  else if( input == "real?" && num != 1 ) return false ; 
  else if( input == "number?" && num != 1 ) return false ; 
  else if( input == "string?" && num != 1 ) return false ; 
  else if( input == "boolean?" && num != 1 ) return false ;
  else if( input == "symbol?" && num != 1 ) return false ;
  else if( input == "+" && num < 2 ) return false ;
  else if( input == "-" && num < 2 ) return false ; 
  else if( input == "*" && num < 2 ) return false ; 
  else if( input == "/" && num < 2 ) return false ;
  else if( input == "not" && num != 1 ) return false ; 
  else if( input == "and" && num < 2 ) return false ; 
  else if( input == "or" && num < 2 ) return false ; 
  else if( input == ">" && num < 2 ) return false ; 
	else if( input == ">=" && num < 2 ) return false ; 
  else if( input == "<" && num < 2 ) return false ;
  else if( input == "<=" && num < 2 ) return false ;
  else if( input == "=" && num < 2 ) return false ;
  else if( input == "string-append" && num < 2 ) return false ;
  else if( input == "string>?" && num < 2 ) return false ;
  else if( input == "string<?" && num < 2 ) return false ;
  else if( input == "string=?" && num < 2 ) return false ;
  else if( input == "eqv?" && num != 2 ) return false ; 
  else if( input == "equal?" && num != 2 ) return false ;
  else if( input == "begin" && num < 1 ) return false ; 
  else return true;
  
} // fuc_arg() 

tree* clone_tree( tree *root ) {
  if( root == NULL )
    return NULL ;
    
  tree *new_node = new tree() ;
  new_node->str = root->str;
  new_node->type = root->type;
  new_node->address = root->address;
  new_node->d = clone_tree(root->d);
  new_node->r = clone_tree(root->r);
  
  return new_node;
} // clone_tree()

tree* quote( tree *root ) {
	tree *a = new tree();
	a = root->r;
  root = root->d->r; 
  root->r = a;
  return root;
} // quote()

tree *getbind( tree *root, vector<def> d ) {
	bool found = false;
  tree *a = new tree();
  a = root -> r;
  
  for( int i = 0; i < d.size() ; i++ ){
    if( root->str == d[i].symbol ) {
      root = clone_tree( d[i].bind );
      root->address = d[i].addr;
      root->type = Gettype( root->str );
      found = true;
    } // if
  } // for
 	
  root -> r = a;
  if(!found) {
  	cout << "> ERROR (unbound symbol) : " << root->str << endl << endl;
  	return NULL;
	} // if     

  return root;
} // getbind()

int arg( tree *root ) {
	int count = 0;
	for( ; root->r->str != ")" ; root = root->r ) 
	  count++;
	return count;
} // arg()

bool non_list( tree *root ) {
  for( ; root->r != NULL ; root = root->r )
    if ( root->str == "." ) return true;
  return false;
} // pure_list()

bool def_format( tree *root ) {
	int k ;
	string input;
	input = "#<procedure " + root->r->str + ">";
	
	if ( root->r->type == "SYMBOL" ){
		if ( isfuc( input, k ) )
		  return false;
		k = arg( root ) ;
		if ( k != 2 ) 
		  return false;
	} // if
	else if ( root->r->type == "LEFT-PAREN" ) {
    k = arg( root ) ;
		if ( k != 2 ) 
		  return false;
		if ( root->r->d->type != "SYMBOL" || root->r->d->str == "quote" ) 
		  return false;
	} // else if
  else {
  	return false;
	}  // else
	
	return true;
} // def_format()

bool cond_format( tree *root ) {
	int count = 0;
	int arg = 0;
	tree *walk = new tree();
  for( ; root->str != ")" ; root = root->r ) {
  	if ( root->str != "(" ) 
  	  return false;
  	if ( non_list( root->d ) )
  	  return false;
    walk = root->d;
    while( walk->str != ")") {
    	arg++;
    	walk = walk->r;
		} // while
		
		if ( arg < 2 ) return false;
  	count++;
  	arg = 0;
	} // for
	
	if ( count < 1 ) return false;
	return true;
} // cond_format()

tree *define( tree *root, int level, vector<def> &d, bool & exit ) { //defined 函式 
  def tmp;
  tmp.symbol = root->str ;
  tmp.bind = new tree();
  tmp.addr = new tree();
  tree *a = new tree();
  
	root->r = eval( root->r, level+1, d, exit );  
  if ( root->r == NULL ) return NULL;
  for( int i = 0; i < d.size(); i++ ) {  //判斷有無重複 
    if( tmp.symbol == d[i].symbol ) {
      d.erase(d.begin()+i );
    } // if
  } // for
	tmp.type = Gettype( root->r->str);
	if ( root->r->address != NULL ) tmp.addr = root->r->address;
	else tmp.addr = root->r;
	tmp.bind = clone_tree( root->r );
	tmp.bind->r = NULL;
	d.push_back(tmp);
	cout << "> " << root->str << " " << "defined" <<endl << endl;

	return NULL;
} // define

tree *exit() {
	cout << "> " << endl;
  return NULL;
} // exit

tree *clean_env( vector<def> &d ) {
  d.clear();
  Add_Fuc( d ) ;
  cout << "> " << "environment cleaned" << endl << endl;
  return NULL;
} // clean_env

tree *If( tree *root, int & level, vector<def> d, bool & end ) {
  tree *temp = new tree() ;
  tree *org = new tree() ;
	org = clone_tree( root ) ;
	org->r = NULL ;
	root = root->d->r;
	root = eval( root, level+1, d, end ) ;
	if ( root == NULL ) return NULL;
  if( root ->type == "NIL" ){
    if ( root->r->r->str == ")" ) {
        org->d->str = org->d->str.substr( 12 ) ;
        org->d->str.erase( org->d->str.begin() + org->d->str.size() -1  );
				int x = 0;
				bool samelines = false;
				cout << "> ERROR (no return value) : ";
	      print( org, x, samelines );
	      cout << endl;
	      return NULL;
    } // if
  	root->r->r->r = NULL;
    temp = root->r->r ;    
  } // if
  else {
  	root->r->r = NULL;
    temp = root->r ;    	
	} // else
    
  temp = eval( temp, level+1, d, end ) ;
  return temp;  
} // If

tree *And( tree *root, int level, vector<def> &d, bool & exit ) {
  tree *temp = new tree();
  while( root != NULL  ){
    root = eval( root, level+1, d, exit) ;
	  if ( root == NULL ) return NULL;
    if( root -> type == "NIL" ) {
      return root;        
    } // if
    if( root -> r -> str  == ")" ) {
      root -> r =  NULL ;
      return root;
    } // if
    root = root -> r ; 
  }   // while
} // And()

tree *Atom( tree *root, int level, vector<def> &d, bool & exit ){
  tree *temp = new tree();
	root = eval( root, level+1, d, exit ) ;
	if ( root == NULL ) return NULL;
  
  if ( root->type == "SYMBOL" || root->type == "INTEGER" || root->type == "FLOAT" ) {
    temp -> str = "#t";
    temp -> type = "T";
    temp -> d = NULL;
    temp -> r = NULL;
    return temp;
  } // if
  else {
    temp -> str = "nil";
    temp -> type = "NIL";
    temp -> d = NULL;
    temp -> r = NULL;
    return temp;   
  } // else
} // Atom()

tree *Or( tree *root, int level, vector<def> &d, bool & exit ){
  tree *temp = new tree();
  while( root != NULL  ){
  	root = eval( root, level+1, d, exit) ;
	  if ( root == NULL ) return NULL;
    if( root -> type != "NIL" ){
      return root;     
    } // if
		 
    if( root -> r -> str  == ")" ){
      return root;
    } // if
    
    root = root -> r ; 
  }  // while
} // Or

tree *Cond( tree *root, int level, vector<def> &d, bool & exit ) {
  tree *temp = new tree();
  tree *org = new tree() ;
	org = clone_tree( root ) ;
	org->r = NULL ;
	root = root->d->r;
  while( root->str != ")" ) {
  	if ( root->d->str == "else" && root->r->str == ")" ) {
    	temp = root->d->r;
    	while( temp->r->str != ")" ) {
    	  temp = eval( temp, level+1, d, exit);
    	  if ( temp == NULL ) return NULL;
    		temp = temp->r;
			} // while	
			
			temp = eval( temp, level+1, d, exit);
    	return temp;
		} // if
		
  	root->d = eval( root->d, level+1, d, exit );
  	if ( root->d == NULL ) return NULL;
    if ( root->d->str != "nil" ) {
    	temp = root->d->r;
    	while( temp->r->str != ")" ) {
    	  temp = eval( temp, level+1, d, exit);
    	  if ( temp == NULL ) return NULL;
    		temp = temp->r;
			} // while

      temp = eval( temp, level+1, d, exit);
    	return temp;
		} // if
  
    root = root -> r ; 
  } // while

  org->d->str = org->d->str.substr( 12 ) ;
  org->d->str.erase( org->d->str.begin() + org->d->str.size() -1  );
	int x = 0;
	bool samelines = false;
	cout << "> ERROR (no return value) : ";
  print( org, x, samelines );
  cout << endl;
  return NULL;

} // Cond

tree *Begin( tree *root, int level, vector<def> &d, bool & exit ){
  tree *temp = new tree();
  //temp = NULL ;
  while( root != NULL ) {
  	root = eval( root, level+1, d, exit) ;
	  if ( root == NULL ) return NULL; 
    if( root -> r -> str  == ")" ){
      return root;
    } // if
    root = root -> r ; 
  } // while
} // Begin()

tree* car( tree *root, int level, vector<def> &d, bool & exit ) {
  root = eval( root, level+1, d, exit) ;
	if ( root == NULL ) return NULL;
		  
  if ( root->str == "(" ) {
  	root->d->address = root->address;
    root = root -> d;
    root ->r = NULL;
  } // if
  else {
  	cout << "> ERROR (car with incorrect argument type) : " << root->str << endl << endl;
  	return NULL;
	} //else
  
  root->type = Gettype( root->str ) ;
  return root;
} // car()

tree* cdr( tree *root, int level, vector<def> &d, bool & exit ) {
  root = eval( root, level+1, d, exit) ;
	if ( root == NULL ) return NULL;
  
  if ( root->str == "(" ) {
  	root -> r = NULL;
    root -> d = root -> d -> r ;
  } //if
  else {
  	cout << "> ERROR (cdr with incorrect argument type) : " << root->str << endl << endl;
  	return NULL;
	} //else

  if( root ->d -> str == ".") {
  	root->d->r->address = root->address;
    root = root ->d -> r;
    root -> r = NULL; 
  } //if
  
  if ( root->str == "(" && root->d->str == ")" ) {
  	tree* temp = new tree();
  	temp->address = root->address;
  	temp->str = "nil";
  	temp->type = "NIL";
  	return temp;
	} // if

  root->type = Gettype( root->str ) ;
  return root;
} // cdr()

tree* cons( tree *root, int level, vector<def> &d, bool & exit ) {
	tree *a = new tree();
	tree *b = new tree();
	tree *c = new tree();
	tree *e = new tree();
  root = eval( root, level+1, d, exit) ;
	if ( root == NULL ) return NULL;
	
  if ( root->str == "(" ) {
  	root->r = eval( root->r, level+1, d, exit) ;
	  if ( root->r == NULL ) return NULL;
    if ( root->r->str == "(" ){
		  a = root;
		  b = root->r;
		  a->r = NULL;
		  b->r = NULL;
		  c = b->d;
		  b->d = a;
		  a->r = c;
		} // else if
		else if ( root->r->str == "" ) {
      b->str = "(";
      b->type = "LEFT-PAREN";
      e->str = ")";
      e->type = "RIGHT-PAREN";
      root->r = e;
      b->d = root;
		} // else if
		else { // atom
      b->str = "(";
      b->type = "LEFT-PAREN";
      c->str = ".";
      c->type = "DOT";
      e->str = ")";
      e->type = "RIGHT-PAREN";
      a = root->r;
      root->r = c;
      c->r = a;
      a->r = e;
      b->d = root;
		} // else
  } // else if
  else { // atom
  	root->r = eval( root->r, level+1, d, exit) ;
	  if ( root->r == NULL ) return NULL;

    if ( root->r->str == "(" ){
		  a = root;
		  b = root->r;
		  a->r = NULL;
		  b->r = NULL;
		  c = b->d;
		  b->d = a;
		  a->r = c;
		} // else if
		else if ( root->r->str == "" ) {
      b->str = "(";
      b->type = "LEFT-PAREN";
      e->str = ")";
      e->type = "RIGHT-PAREN";
      root->r = e;
      b->d = root;
		} // else if
		else { // atom
		  a = root;
		  e = root->r;
		  a->r = NULL;
		  c->str = ".";
		  a->r = c;
		  c->r = e;	
		  b->str = "(";
		  b->d = a;
		} // else
	} // else
	
	for ( a = b->d; a->r != NULL; a = a -> r ) {
		if ( a->r->r != NULL && a->r->str == "." && a->r->r->str == "nil" ) 
		  a->r = a->r->r->r;  
	} // for

	b->address = b;
  b->type = Gettype( b->str ) ;
  return b;
} // cons()

tree* list( tree *root, int level, vector<def> &d, bool & exit ) {
	tree *a = new tree();
	tree *b = new tree();
	tree *head = new tree();
	head = root;
	for ( ; root->r->r != NULL ; root = root->r ) {
  	root->r = eval( root->r, level+1, d, exit) ;
	  if ( root->r == NULL ) return NULL;
  } //  for
  
  b->str = "(";
  b->type = "LEFT-PAREN";
  head = head->r;
  b->d = head;
  if ( b->str == "(" && b->d->str == ")" ) {
  	b = new tree();
  	b->str = "nil";
  	b->type = "NIL";
	} //if
 
  b->type = Gettype( b->str ) ;
  return b;
} // list()


tree *c_list( tree *root, int level, vector<def> &d, bool & exit ) {
	bool found = true;
	tree *temp = new tree();
	root = eval( root, level+1, d, exit) ;
  if ( root == NULL ) return NULL;
  
	if ( root->str == "(" ){
		root = root->d;
		for( ; root->r != NULL ; root = root->r ) {
			if ( root->str == "." && root->r->str != "(") found = false;
		} // for
	} // if
	else if ( root->str == "nil" && root->r->str == ")" ) 
	  found = true;
  else 
    found = false;
	
	if ( found ) {
	  temp->str = "#t";
	  temp->type = "T";
	} // if
	else {
	  temp->str = "nil";
	  temp->type = "NIL";
	} //else
	
  return temp;		   
} // c_list() 

tree *boolean( tree *root, int level, vector<def> &d, bool & exit ){
  tree *temp = new tree();
	root = eval( root, level+1, d, exit) ;
  if ( root == NULL ) return NULL;

  if( root ->  type == "NIL" ||  root -> type == "T"  ){
    temp -> str = "#t";
    temp -> type = "T";
    return temp;
  }
  else{
    temp -> str = "nil";
    temp -> type = "NIL";
    return temp;  
  }
}

tree *str( tree *root, int level, vector<def> &d, bool & exit ){
  tree *temp = new tree();
	root = eval( root, level+1, d, exit) ;
  if ( root == NULL ) return NULL;

  if( root -> type == "STRING"   ){       /////////////////////////////////// [0]
    temp -> str = "#t";
    temp -> type = "T";
    return temp;
  }
  else{
    temp -> str = "nil";
    temp -> type = "NIL";
    return temp;  
  }
}

tree *null( tree *root, int level, vector<def> &d, bool & exit ){
	root = eval( root, level+1, d, exit) ;
  if ( root == NULL ) return NULL;

  tree *temp = new tree();
  if( root -> type == "NIL"   ){
    temp -> str = "#t";
    temp -> type = "T";
    return temp;
  }
  else{
    temp -> str = "nil";
    temp -> type = "NIL";
    return temp;  
  }  
}

tree *Integer( tree *root, int level, vector<def> &d, bool & exit ){
  tree *temp = new tree();
	root = eval( root, level+1, d, exit) ;
  if ( root == NULL ) return NULL;

  if( root->type == "INTEGER" ){
    temp -> str = "#t";
    temp -> type = "T";
    return temp;
  } 
  temp -> str = "nil";
  temp -> type = "NIL";
  return temp;   
}


tree *Number( tree *root, int level, vector<def> &d, bool & exit ) {
  tree *temp = new tree();
	root = eval( root, level+1, d, exit) ;
  if ( root == NULL ) return NULL;
  
  if( root->type == "INTEGER" || root->type == "FLOAT" ){
    temp -> str = "#t";
    temp -> type = "T";
    return temp;
  } 
  temp -> str = "nil";
  temp -> type = "NIL";
  return temp;   
}

tree *Real( tree *root, int level, vector<def> &d, bool & exit ){
  tree *temp = new tree();
	root = eval( root, level+1, d, exit) ;
  if ( root == NULL ) return NULL;
  
  if( root->type == "INTEGER" || root->type == "FLOAT" ){
    temp -> str = "#t";
    temp -> type = "T";
    return temp;
  }
  temp -> str = "nil";
  temp -> type = "NIL";
  return temp;   
}


tree *Pair( tree *root, int level, vector<def> &d, bool & exit ) {
  tree *temp = new tree();
	root = eval( root, level+1, d, exit) ;
  if ( root == NULL ) return NULL;
 
  if ( root-> d != NULL){
    temp -> str = "#t";
    temp -> type = "T";
    return temp;
  }
  else {
    temp -> str = "nil";
    temp -> type = "NIL";
    return temp;   
  }
}


tree* Symbol( tree *root, int level, vector<def> &d, bool & exit ) {
  tree *temp = new tree();
	root = eval( root, level+1, d, exit) ;
  if ( root == NULL ) return NULL;
  
  if ( root->type == "SYMBOL" ) { // symbol
    tree *a = new tree();
    for( int i = 0; i < d.size(); i++ ){
      if( root->str == d[i].symbol &&  d[i].type == "SYMBOL" ){
        temp -> str = "#t";
        temp -> type = "T";
        return temp;
      } // if
      else if( root->str == d[i].symbol &&  d[i].type != "SYMBOL" ){
        temp -> str = "nil";
        temp -> type = "NIL";
        return temp;     
      }
    } // for
    temp -> str = "#t";
    temp -> type = "T";
    return temp;
  } // if
  else {
    temp -> str = "nil";
    temp -> type = "NIL";
    return temp;   
  } // else
} // Symbol()

tree *Minus( tree *root, int level, vector<def> &d, bool & exit ) {
  double result = 1;
  bool num = false, flo = false;
  tree *tmp = new tree();
  tree *walk = root;
  while( walk->r -> r != NULL ){
    //cout << root->str;
    walk->r = eval( walk->r, level+1, d, exit  );
    if( walk->r == NULL ) {
      return NULL ;
    }
 
    if( isInteger( walk->r->str ) == true ){
    }
    else if ( Isfloat( walk->r->str ) == true ){
    }
    else {
      cout << "> " << "ERROR (- with incorrect argument type) : " ;
      int x = 0;
      bool sameline = false ;
      walk->r -> r = NULL ;
      print( walk->r, x, sameline );
      cout << endl;
      return NULL;
    }
    walk = walk ->r ;
  }
  
  root = root -> r ;
  if( isInteger( root->str ) == true ) {
    int i = 0; 
    double value = 0, sign = 1;     
    while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
      if( root->str[0] == '-' ) {
        sign = -1;
        i++ ;
      }
      value = value * 10 + ( root->str[i] - '0');
      i++;
    }
    value *= sign;
    result = value ;
  }    
  else if ( Isfloat( root->str ) == true ){
	  double val = Stod(root->str); 
	  result = val;
	  flo = true ;
  }
 
  root = root->r ;
  while( root -> r != NULL ){
  
    if( isInteger( root->str ) == true ){
      int i = 0; 
      double value = 0, sign = 1;
      
      while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
        if( root->str[0] == '-' ) {
          sign = -1;
          i++ ;
        }
        value = value * 10 + ( root->str[i] - '0');
        i++;
      }
      value *= sign;
      result -= value;
    }
    else if ( Isfloat( root->str ) == true ){
		  double val = Stod(root->str); 
		  result -= val;
		  flo = true ;
    }
    root = root ->r ;
  }
  if( flo == true ){
		stringstream ss;
		ss << fixed << setprecision(3) << result; 
		tmp->str = ss.str();
    tmp->type = "FLOAT";     
  }
  else{
		stringstream ss;
		ss <<  result; 
		tmp->str = ss.str();
    tmp->type = "INTEGER";      
  }
  return tmp;
} 

tree *Plus( tree *root, int level, vector<def> &d, bool & exit ) {
  double result = 0;
  bool num = false, flo = false;
  tree *tmp = new tree();
  tree *walk = root;
  while( walk->r -> r != NULL ){
    //cout << root->str;
    walk->r = eval( walk->r, level+1, d, exit  );
    if( walk->r == NULL ) {
      return NULL ;
    }
 
    if( isInteger( walk->r->str ) == true ){
    }
    else if ( Isfloat( walk->r->str ) == true ){
    }
    else {
      cout << "> " << "ERROR (+ with incorrect argument type) : " ;
      int x = 0;
      bool sameline = false ;
      walk->r -> r = NULL ;
      print( walk->r, x, sameline );
      cout << endl;
      return NULL;
    }
    walk = walk ->r ;
  }
  
  root = root -> r ;
  
  while( root -> r != NULL ){
  	  
    if( isInteger( root->str ) == true ){
      int i = 0; 
      double value = 0;
      value = Stod(root->str) ;
      result += value;
    }
    else if ( Isfloat( root->str ) == true ){
		  double val = Stod(root->str); 
		  result += val;
		  flo = true ;
    }
    root = root ->r ;
  }
  if( flo == true ){
		stringstream ss;
		ss << fixed << setprecision(3) << result; 
		tmp->str = ss.str();
    tmp->type = "FLOAT";     
  }
  else{
		stringstream ss;
		ss <<  result; 
		tmp->str = ss.str();
    tmp->type = "INTEGER";      
  } // else
  return tmp;
}  


tree *Mult( tree *root, int level, vector<def> &d, bool & exit ) {
  double result = 1;
  bool num = false, flo = false;
  tree *tmp = new tree();
  tree *walk = root;
  while( walk->r -> r != NULL ){
    //cout << root->str;
    walk->r = eval( walk->r, level+1, d, exit  );
    if( walk->r == NULL ) {
      return NULL ;
    }
 
    if( isInteger( walk->r->str ) == true ){
    }
    else if ( Isfloat( walk->r->str ) == true ){
    }
    else {
      cout << "> " << "ERROR (* with incorrect argument type) : " ;
      int x = 0;
      bool sameline = false ;
      walk->r -> r = NULL ;
      print( walk->r, x, sameline );
      cout << endl;
      return NULL;
    }
    walk = walk ->r ;
  }
  
  root = root -> r ;
  while( root -> r != NULL ){
    
    
    if( isInteger( root->str ) == true ){
      int i = 0; 
      double value = 0, sign = 1;
      
      while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
        if( root->str[0] == '-' ) {
          sign = -1;
          i++ ;
        }
        value = value * 10 + ( root->str[i] - '0');
        i++;
      }
      value *= sign;
      result *= value;
    }
    else if ( Isfloat( root->str ) == true ){
		  double val = Stod(root->str); 
		  result *= val;
		  flo = true ;
    }
    root = root ->r ;
  }
  if( flo == true ){
		stringstream ss;
		ss << fixed << setprecision(3) << result; 
		tmp->str = ss.str();
    tmp->type = "FLOAT";     
  }
  else{
    
		stringstream ss;
		ss <<  result; 
		tmp->str = ss.str();
    tmp->type = "INTEGER";      
  }
  return tmp;
}  


tree *Div( tree *root, int level, vector<def> &d, bool & exit ) {
  double result = 1;
  bool num = false, flo = false;
  tree *tmp = new tree();
  tree *walk = root;
  while( walk->r -> r != NULL ){
    //cout << root->str;
    walk->r = eval( walk->r, level+1, d, exit  );
    if( walk->r == NULL ) {
      return NULL ;
    }
 
    if( isInteger( walk->r->str ) == true ){
    }
    else if ( Isfloat( walk->r->str ) == true ){
    }
    else {
      cout << "> " << "ERROR (/ with incorrect argument type) : " ;
      int x = 0;
      bool sameline = false ;
      walk->r -> r = NULL ;
      print( walk->r, x, sameline );
      cout << endl;
      return NULL;
    }
    walk = walk ->r ;
  }
  
  root = root -> r ;
  if( isInteger( root->str ) == true ) {
    int i = 0; 
    double value = 0, sign = 1;     
    while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
      if( root->str[0] == '-' ) {
        sign = -1;
        i++ ;
      }
      value = value * 10 + ( root->str[i] - '0');
      i++;
    }
    value *= sign;
    result = value ;
  }    
  else if ( Isfloat( root->str ) == true ){
	  double val = Stod(root->str); 
	  result = val;
	  flo = true ;
  }
  
  root = root->r ;
  while( root -> r  != NULL ){
    if( isInteger( root->str ) == true ){
      int i = 0; 
      double value = 0, sign = 1;
      
      while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
        if( root->str[0] == '-' ) {
          sign = -1;
          i++ ;
        }
        value = value * 10 + ( root->str[i] - '0');
        i++;
      }
      if( value == 0 ){
        cout << "> " << "ERROR (division by zero) : /" << endl << endl ;
        return NULL;
      }
      value *= sign;
      result /= value;
    }
    else if ( Isfloat( root->str ) == true ){
		  double val = Stod(root->str); 
		  result /= val;
		  flo = true ;
    }
    root = root ->r ;
  }
  if( flo == true ){
		stringstream ss;
		ss << fixed << setprecision(3) << result; 
		tmp->str = ss.str();
    tmp->type = "FLOAT";     
  }
  else{
    
		stringstream ss;
		ss <<  (int)result; 
		tmp->str = ss.str();
    tmp->type = "INTEGER";      
  }
  return tmp;
} 

tree *Not( tree *root, int level, vector<def> &d, bool & exit ) {
	root = eval( root, level+1, d, exit) ;
  if ( root == NULL ) return NULL;
  
  tree *temp = new tree();
  if( root -> type == "NIL"   ){
    temp -> str = "#t";
    temp -> type = "T";
    return temp;
  }
  else{
    temp -> str = "nil";
    temp -> type = "NIL";
    return temp;  
  }  
}

void compare( tree *root, string & s ) {
  if( root == NULL )
    return ;
  s = s + root->str;
  compare(root->d, s);
  compare(root->r, s);
} // compare

tree* equ( tree *root, int level, vector<def> &d, bool & exit ) {
	bool found = true;
	string s1, s2;
	tree* temp = new tree();
	temp = root->r;
  root->r = NULL;
  temp->r = NULL;
  root = eval( root, level+1, d, exit );
  if( root == NULL ) return NULL; 

  temp = eval( temp, level+1, d, exit );
  if( temp == NULL ) return NULL; 

	compare( root, s1 );
	compare( temp, s2 );
	if ( s1 != s2 ) found = false;
	if ( found ) {
	  temp = new tree();
	  temp->str = "#t";
	  temp->type = "T";
		return temp;
	} // if
	else {
	  temp = new tree();
	  temp->str = "nil";
	  temp->type = "NIL";
		return temp;		
	} //else

} // equ()

tree* eqv( tree *root, int level, vector<def> &d, bool & exit ) {
	bool found = true;
	string s1, s2;
	tree* temp = new tree();
	temp = root->r;
  root->r = NULL;
  temp->r = NULL;  
  if ( root->type != "SYMBOL" && root->type != "LEFT-PAREN" && root->type != "STRING"  ) {
  	if ( root->str != temp->str ) found = false;
	} // if
	else {
    root = eval( root, level+1, d, exit );
    if( root == NULL ) return NULL; 
  
    temp = eval( temp, level+1, d, exit );
    if( temp == NULL ) return NULL;
  	compare( root, s1 );
  	compare( temp, s2 );
  	if ( s1 != s2 ) found = false;
  	if ( root->address != temp->address ) found = false;
  	if ( root->address == NULL &&  temp->address == NULL ) found = false;
  } // else

  temp = new tree();
	if ( found ) {
	  temp->str = "#t";
	  temp->type = "T";
	} // if
	else {
	  temp->str = "nil";
	  temp->type = "NIL";		
	} //else
	
	return temp;
} // eqv()

tree *Greater( tree *root, int level, vector<def> &d, bool & exit ) {
  double result = 0;
  bool hasFail = false;
  string com = "";
  tree *temp = new tree();
  tree *walk = root;
  while( walk -> r ->r != NULL ){
    
    walk->r = eval( walk->r, level+1, d, exit  );
    if( walk->r == NULL ){
      return NULL ;
    }
    if( isInteger( walk->r->str ) == true ){
    }
    else if ( Isfloat( walk->r->str ) == true ){
    }
    else if( walk->r->type == "STRING" ){
    }
    else {
      cout << "> " << "ERROR (> with incorrect argument type) : " ;
      int x = 0;
      bool sameline = false ;
      walk->r -> r = NULL ;
      print( walk->r, x, sameline );
      cout << endl;
      return NULL;
    }
    walk = walk ->r ;
  }
  root = root ->r ;
  if( isInteger( root->str ) == true ) {
    int i = 0; 
    double value = 0, sign = 1;     
    while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
      if( root->str[0] == '-' ) {
        sign = -1;
        i++ ;
      }
      value = value * 10 + ( root->str[i] - '0');
      i++;
    }
    value *= sign;
    result = value ;
  }    
  else if ( Isfloat( root->str ) == true ){
		double val = Stod(root->str); 
		result = val;
  }
  else if( root->type == "STRING" )    {
    com = root->str;
  }
  
  root = root->r ;
  
  while( root ->r != NULL ){

    if( isInteger( root->str ) == true ){
      int i = 0; 
      double value = 0, sign = 1;
      
      
      while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
        if( root->str[0] == '-' ) {
          sign = -1;
          i++ ;
        }
        value = value * 10 + ( root->str[i] - '0');
        i++;
      }
      value *= sign;
      if( result > value ){
        result = value ;
      } 
      else{
        hasFail = true;
        temp -> str = "nil";
        temp -> type = "NIL";
        return temp;        
      }
    }
    else if ( Isfloat( root->str ) == true ){
		  double val = Stod(root->str); 
      if( result > val ){
        result = val ;
      } 
      else{
        hasFail = true;
        temp -> str = "nil";
        temp -> type = "NIL";
        return temp;        
      }
    }
    else if( root->type == "STRING" )    {
      com = root->str;
    }
    root = root ->r ;
  }
  
  if( hasFail == false ){
    temp -> str = "#t";
    temp -> type = "T";
    return temp;       
  }  
} 


tree *BigandEqual( tree *root, int level, vector<def> &d, bool & exit ) {
  double result = 0;
  bool hasFail = false;
  string com;
  tree *temp = new tree();
  tree *walk = root;
  while( walk -> r ->r != NULL ){
    
    walk->r = eval( walk->r, level+1, d, exit  );
    if( walk->r == NULL ){
      return NULL ;
    }
    if( isInteger( walk->r->str ) == true ){
    }
    else if ( Isfloat( walk->r->str ) == true ){
    }
    else if( walk->r->type == "STRING" ){
    }
    else {
      cout << "> " << "ERROR (>= with incorrect argument type) : " ;
      int x = 0;
      bool sameline = false ;
      walk->r -> r = NULL ;
      print( walk->r, x, sameline );
      cout << endl;
      return NULL;
    }
    walk = walk ->r ;
  }
  root = root ->r ;
  if( isInteger( root->str ) == true ) {
    int i = 0; 
    double value = 0, sign = 1;     
    while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
      if( root->str[0] == '-' ) {
        sign = -1;
        i++ ;
      }
      value = value * 10 + ( root->str[i] - '0');
      i++;
    }
    value *= sign;
    result = value ;
  }    
  else if ( Isfloat( root->str ) == true ){
		double val = Stod(root->str); 
		result = val;
  }
  else if( root->type == "STRING" )    {
    com = root->str;
  }
  root = root->r ;
  
  while( root -> r != NULL ){
    root = eval( root, level+1, d, exit  );
    if( root == NULL )  return NULL ;

    if( isInteger( root->str ) == true ){
      int i = 0; 
      double value = 0, sign = 1;
      
      while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
        if( root->str[0] == '-' ) {
          sign = -1;
          i++ ;
        }
        value = value * 10 + ( root->str[i] - '0');
        i++;
      }
      value *= sign;
      if( result >= value ){
        result = value ;
      } 
      else{
        hasFail = true;
        temp -> str = "nil";
        temp -> type = "NIL";
        return temp;        
      }
    }
    else if ( Isfloat( root->str ) == true ){
		  double val = Stod(root->str); 
      if( result >= val ){
        result = val ;
      } 
      else{
        hasFail = true;
        temp -> str = "nil";
        temp -> type = "NIL";
        return temp;        
      }
    }
    else if( root->type == "STRING" )    {
      com = root->str;
    }
    root = root ->r ;
  }
  
  if( hasFail == false ){
    temp -> str = "#t";
    temp -> type = "T";
    return temp;       
  }  
} 

tree *Smaller( tree *root, int level, vector<def> &d, bool & exit ) {
  double result = 0;
  bool hasFail = false;
  string com = ""; 
  tree *temp = new tree();
  tree *walk = root;
  while( walk -> r ->r != NULL ){
    
    walk->r = eval( walk->r, level+1, d, exit  );
    if( walk->r == NULL ){
      return NULL ;
    }
    if( isInteger( walk->r->str ) == true ){
    }
    else if ( Isfloat( walk->r->str ) == true ){
    }
    else if( walk->r->type == "STRING" ){
    }
    else {
      cout << "> " << "ERROR (< with incorrect argument type) : " ;
      int x = 0;
      bool sameline = false ;
      walk->r -> r = NULL ;
      print( walk->r, x, sameline );
      cout << endl;
      return NULL;
    }
    walk = walk ->r ;
  }
  root = root ->r ;
  if( isInteger( root->str ) == true ) {
    int i = 0; 
    double value = 0, sign = 1;     
    while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
      if( root->str[0] == '-' ) {
        sign = -1;
        i++ ;
      }
      value = value * 10 + ( root->str[i] - '0');
      i++;
    }
    value *= sign;
    result = value ;
  }    
  else if ( Isfloat( root->str ) == true ){
		double val = Stod(root->str); 
		result = val;
  }
  else if( root->type == "STRING" )    {
    com = root->str;
  }
  root = root->r ;
  
  while( root -> r != NULL ){
    root = eval( root, level+1, d, exit  );
    if( root == NULL )  return NULL ;
 
    if( isInteger( root->str ) == true ){
      int i = 0; 
      double value = 0, sign = 1;
      
      while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
        if( root->str[0] == '-' ) {
          sign = -1;
          i++ ;
        }
        value = value * 10 + ( root->str[i] - '0');
        i++;
      }
      value *= sign;
      if( result < value ){
        result = value ;
      } 
      else{
        hasFail = true;
        temp -> str = "nil";
        temp -> type = "NIL";
        return temp;        
      }
    }
    else if ( Isfloat( root->str ) == true ){
		  double val = Stod(root->str); 
      if( result < val ){
        result = val ;
      } 
      else{
        hasFail = true;
        temp -> str = "nil";
        temp -> type = "NIL";
        return temp;        
      }
    }
    else if( root->type == "STRING" )    {
      com = root->str;
    }
    root = root ->r ;
  }
  
  if( hasFail == false ){
    temp -> str = "#t";
    temp -> type = "T";
    return temp;       
  }  
} 


tree *SmallandEqual( tree *root, int level, vector<def> &d, bool & exit ) {
  double result = 0;
  string com = "";
  bool hasFail = false;
  tree *temp = new tree();
  tree *walk = root;
  while( walk -> r ->r != NULL ){
    
    walk->r = eval( walk->r, level+1, d, exit  );
    if( walk->r == NULL ){
      return NULL ;
    }
    if( isInteger( walk->r->str ) == true ){
    }
    else if ( Isfloat( walk->r->str ) == true ){
    }
    else if( walk->r->type == "STRING" ){
    }
    else {
      cout << "> " << "ERROR (<= with incorrect argument type) : " ;
      int x = 0;
      bool sameline = false ;
      walk->r -> r = NULL ;
      print( walk->r, x, sameline );
      cout << endl;
      return NULL;
    }
    walk = walk ->r ;
  }
  root = root ->r ;
  if( isInteger( root->str ) == true ) {
    int i = 0; 
    double value = 0, sign = 1;     
    while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
      if( root->str[0] == '-' ) {
        sign = -1;
        i++ ;
      }
      value = value * 10 + ( root->str[i] - '0');
      i++;
    }
    value *= sign;
    result = value ;
  }    
  else if ( Isfloat( root->str ) == true ){
		double val = Stod(root->str); 
		result = val;
  }
  else if( root->type == "STRING" )    {
    com = root->str;
  }
  root = root->r ;
  
  while( root -> r!= NULL ){
    //cout << root->str;
    root = eval( root, level+1, d, exit  );
    if( root == NULL )  return NULL ;
 
    if( isInteger( root->str ) == true ){
      int i = 0; 
      double value = 0, sign = 1;
      
      while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
        if( root->str[0] == '-' ) {
          sign = -1;
          i++ ;
        }
        value = value * 10 + ( root->str[i] - '0');
        i++;
      }
      value *= sign;
      if( result <= value ){
        result = value ;
      } 
      else{
        hasFail = true;
        temp -> str = "nil";
        temp -> type = "NIL";
        return temp;        
      }
    }
    else if ( Isfloat( root->str ) == true ){
		  double val = Stod(root->str); 
      if( result <= val ){
        result = val ;
      } 
      else{
        hasFail = true;
        temp -> str = "nil";
        temp -> type = "NIL";
        return temp;        
      }
    }
    else if( root->type == "STRING" )    {
      com = root->str;
    }
    root = root ->r ;
  }
  
  if( hasFail == false ){
    temp -> str = "#t";
    temp -> type = "T";
    return temp;       
  }  
} 


tree *Equal( tree *root, int level, vector<def> &d, bool & exit ) {
  double result = 0;
  bool hasFail = false;
  string com  = "" ;
  tree *temp = new tree();
  tree *walk = root;
  while( walk -> r ->r != NULL ){
    
    walk->r = eval( walk->r, level+1, d, exit  );
    if( walk->r == NULL ){
      return NULL ;
    }
    if( isInteger( walk->r->str ) == true ){
    }
    else if ( Isfloat( walk->r->str ) == true ){
    }
    else if( walk->r->type == "STRING" ){
    }
    else {
      cout << "> " << "ERROR (= with incorrect argument type) : " ;
      int x = 0;
      bool sameline = false ;
      walk->r -> r = NULL ;
      print( walk->r, x, sameline );
      cout << endl;
      return NULL;
    }
    walk = walk ->r ;
  }
  root = root ->r ;
  if( isInteger( root->str ) == true ) {
    int i = 0; 
    double value = 0, sign = 1;     
    while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
      if( root->str[0] == '-' ) {
        sign = -1;
        i++ ;
      }
      value = value * 10 + ( root->str[i] - '0');
      i++;
    }
    value *= sign;
    result = value ;
  }    
  else if ( Isfloat( root->str ) == true ){
		double val = Stod(root->str); 
		result = val;
  }
  else if( root->type == "STRING" )    {
    com = root->str;
  }
  root = root->r ;
  
  while( root -> r != NULL ){
    //cout << root->str;
    if ( root->type == "SYMBOL" ) { // symbol      
      root = getbind( root, d) ;        
      if( root == NULL )
        return NULL;    
    }
 
    if( isInteger( root->str ) == true ){
      int i = 0; 
      double value = 0, sign = 1;
      
      while ( ( i < root->str.length() && isdigit( root->str[i]) ) || root->str[i] == '-' ) {
        if( root->str[0] == '-' ) {
          sign = -1;
          i++ ;
        }
        value = value * 10 + ( root->str[i] - '0');
        i++;
      }
      value *= sign;
      if( result == value ){
        result = value ;
      } 
      else{
        hasFail = true;
        temp -> str = "nil";
        temp -> type = "NIL";
        return temp;        
      }
    }
    else if ( Isfloat( root->str ) == true ){
		  double val = Stod(root->str); 
      if( result == val ){
        result = val ;
      } 
      else{
        hasFail = true;
        temp -> str = "nil";
        temp -> type = "NIL";
        return temp;        
      }
    }
    else if( root->type == "STRING" )    {
      com = root->str;
    }
    root = root ->r ;
  }
  
  if( hasFail == false ){
    temp -> str = "#t";
    temp -> type = "T";
    return temp;       
  }  
} 

tree* string_append( tree *root, int level, vector<def> &d, bool & exit ) {
	bool found = true;
	tree * temp = new tree();
  tree *walk = root;
  while( walk->r->r != NULL ) {
	  walk->r = eval( walk->r, level+1, d, exit) ;
    if ( walk->r == NULL ) return NULL;
   
    if( walk->r->type == "STRING" ){
    }
    else {
      cout << "> " << "ERROR (string-append with incorrect argument type) : " ;
      int x = 0;
      bool sameline = false ;
      walk -> r ->r= NULL ;
      print( walk->r, x, sameline );
      cout << endl;
      return NULL;
    }
    walk = walk ->r ;
  } // while
  
	string s, sub;
	for( temp = root->r ; temp->r != NULL ; temp = temp->r ) {
    sub = temp->str.substr( 1, temp->str.size()-2 );
		s = s + sub;				
	} // for
  
  temp = new tree();
  temp->str = "\"" + s + "\"";
  temp->type = "STRING";
  return temp;
} // string_append()

tree* string_bigger( tree *root, int level, vector<def> &d, bool & exit ) {
	bool found = true;
	tree * temp = new tree();
  tree *walk = root;
  while( walk -> r-> r != NULL ){
	  walk->r = eval( walk->r, level+1, d, exit) ;
    if ( walk->r == NULL ) return NULL;
     
    if( walk->r->type == "STRING" ){
    } // if
    else {
      cout << "> " << "ERROR (string>? with incorrect argument type) : " ;
      int x = 0;
      bool sameline = false ;
      walk -> r ->r= NULL ;
      print( walk->r, x, sameline );
      cout << endl;
      return NULL;
    } // else
    walk = walk ->r ;
  } // while
  
	for( temp = root->r ; temp->r->str != ")" ; temp = temp->r ) {
		if ( temp->str <= temp->r->str ) found = false; 
  }
	if ( found ) {
	  temp = new tree();
	  temp->str = "#t";
	  temp->type = "T";
		return temp;
	} // if
	else {
	  temp = new tree();
	  temp->str = "nil";
	  temp->type = "NIL";
		return temp;		
	} //else
} // string_bigger()

tree* string_smaller( tree *root, int level, vector<def> &d, bool & exit ) {
	bool found = true;
	tree * temp = new tree();
  tree *walk = root;
  while( walk -> r-> r != NULL ) {
	  walk->r = eval( walk->r, level+1, d, exit) ;
    if ( walk->r == NULL ) return NULL;
     
    if( walk->r->type == "STRING" ) {
    } // if
    else {
      cout << "> " << "ERROR (string<? with incorrect argument type) : " ;
      int x = 0;
      bool sameline = false ;
      walk -> r ->r= NULL ;
      print( walk->r, x, sameline );
      cout << endl;
      return NULL;
    } // else
    
    walk = walk ->r ;
  } // while
  
	for( temp = root->r ; temp->r->str != ")" ; temp = temp->r ) {
		if ( temp->str >= temp->r->str ) found = false; 
  }
	if ( found ) {
	  temp = new tree();
	  temp->str = "#t";
	  temp->type = "T";
		return temp;
	} // if
	else {
	  temp = new tree();
	  temp->str = "nil";
	  temp->type = "NIL";
		return temp;		
	} //else
} // string_smaller()

tree* string_equal( tree *root, int level, vector<def> &d, bool & exit ) {
	bool found = true;
	tree * temp = new tree();
  tree *walk = root;
  while( walk -> r-> r != NULL ){
	  walk->r = eval( walk->r, level+1, d, exit) ;
    if ( walk->r == NULL ) return NULL;
      
    if( walk->r->type == "STRING" ) {
    } // if
    else {
      cout << "> " << "ERROR (string=? with incorrect argument type) : " ;
      int x = 0;
      bool sameline = false ;
      walk -> r ->r= NULL ;
      print( walk->r, x, sameline );
      cout << endl;
      return NULL;
    } // else
    
    walk = walk ->r ;
  } // while
  
	for( temp = root->r ; temp->r->str != ")" ; temp = temp->r ) {
		if ( temp->str != temp->r->str ) found = false; 
  }
	if ( found ) {
	  temp = new tree();
	  temp->str = "#t";
	  temp->type = "T";
		return temp;
	} // if
	else {
	  temp = new tree();
	  temp->str = "nil";
	  temp->type = "NIL";
		return temp;		
	} //else
} // string_equal()

bool error( tree *root, int level, vector<def> d, bool & exit ) {
	int fuc = 0 ;
  if ( non_list( root->d ) ) {   // not a pure list
  	cout << "> " << "ERROR (non-list) : ";
    int x = 0;
    bool sameline = false ;
    root->r = NULL;
    print( root, x, sameline );
    cout << endl;
  	return false;
	} //  if
  else if ( root->type == "INTEGER" &&  root->type == "FLOAT" && root->type == "STRING" && root->type == "NIL" && root->type == "T" ) {    // first argument not a symbol
		cout << "> " << "ERROR (attempt to apply non-function) : " ;   
		int x = 0;
    bool sameline = false ;
    root->d->r = NULL;
    print( root->d, x, sameline );
    cout << endl;
  	return false;
	} // else if
	else if ( root->d->type == "SYMBOL" ) {    // first argument is a symbol 	  
	  root->d = getbind( root->d, d ) ;
	  if ( root->d == NULL ) 
		  return NULL;
		if ( isfuc( root->d->str, fuc ) ) {    // is the name of a known function
			if ( ( fuc == 1 || fuc == 2 || fuc == 3 ) && level != 0 ) {  //clean-environment, define, exit
        if ( fuc == 1 )  // define
          cout << "> " << "ERROR (level of DEFINE)" << endl << endl ;
        else if ( fuc == 2 )  // exit
          cout << "> " << "ERROR (level of EXIT)" << endl << endl ;
        else if ( fuc == 3 )  // clean-environment
          cout << "> " << "ERROR (level of CLEAN-ENVIRONMENT)" << endl << endl ;
        return false ;
			} // if
			else if ( root->d->str == "#<procedure define>" ) { // define 
		  	if ( !def_format( root->d ) ) {
			    root->d->str = root->d->str.substr( 12 ) ;
          root->d->str.erase( root->d->str.begin() + root->d->str.size() -1  );
					cout << "> " << "ERROR (DEFINE format) : " ;
			    int x = 0;
			    bool sameline = false ;
			    root->r = NULL;
			    print( root, x, sameline );
			    cout << endl;
			  	return false;
				} // if
		  } // else if 
		  else if( root->d->str == "#<procedure cond>"  ) { // cond
		  	if ( !cond_format( root->d->r ) ) {
			    root->d->str = root->d->str.substr( 12 ) ;
          root->d->str.erase( root->d->str.begin() + root->d->str.size() -1  );
					cout << "> " << "ERROR (COND format) : " ;
			    int x = 0;
			    bool sameline = false ;
			    root->r = NULL;
			    print( root, x, sameline );
			    cout << endl;
			  	return false;
				} // if
			} // else if
			else {  // other function
			  int num = arg( root->d );
			  if ( !fuc_arg( root->d->str, num ) ) {
			    string tmp = root->d->str.substr( 12 ) ;
          tmp.erase( tmp.begin() + tmp.size() -1  );
			  	cout << "> " << "ERROR (incorrect number of arguments) : " << tmp << endl << endl ; //要記得改input 
			  	return false;
				} // if
		  } // else
		} // if
		else {  // is not the name of a known function
			cout << "> " << "ERROR (attempt to apply non-function) : " ;
	    int x = 0;
	    bool sameline = false ;
	    root->d->r = NULL;
	    print( root->d, x, sameline );
	    cout << endl;
	  	return false;
		} // else
	} // else if 
  else {  // ((......) .......)
    tree *head = new tree();
    head = root->d->r ;
    root->d->r = NULL;
    root->d = eval( root->d, level+1, d, exit ) ;
    if ( root->d == NULL ) return false;
    root->d->r = head;
	
    if ( isfuc( root->d->str, fuc ) ) {
		  int num = arg( root->d );
		  if ( !fuc_arg( root->d->str, num ) ) {
			  string tmp = root->d->str.substr( 12 ) ;
        tmp.erase( tmp.begin() + tmp.size() -1  );
			  cout << "> " << "ERROR (incorrect number of arguments) : " << tmp << endl << endl ; //要記得改input 
		  	return false;
			} // if
		} // if
		else {
			cout << "> " << "ERROR (attempt to apply non-function) : " ;   
			int x = 0;
	    bool sameline = false ;
	    root->d->r = NULL;
	    print( root->d, x, sameline );
	    cout << endl;
	  	return false;
		} // else
  } // else 
  
	return true;
} // error
 
tree *call( string input, tree *root, int & level, vector<def> &d, bool & end ){
	tree *temp = new tree();
	temp = root;
  input = input.substr( 12 ) ;
  input.erase( input.begin() + input.size() -1  );
  if( input == "define" ) temp = define( root->d->r, level, d, end ) ;
  else if( input == "exit" ) {
  	temp = exit();
  	end = true;
	} // else if
  else if( input == "clean-environment" ) temp = clean_env( d ) ;
  else if( input == "cons" ) temp = cons(root->d->r, level, d, end) ;
  else if( input == "cond" ) temp = Cond(root, level, d, end) ;
  else if( input == "if" ) temp = If(root, level, d, end) ;
  else if( input == "list" ) temp = list(root->d, level, d, end) ;
  else if( input == "quote" ) temp = quote( root );
  else if( input == "car" ) temp = car(root->d->r, level, d, end) ;
  else if( input == "cdr" ) temp = cdr(root->d->r, level, d, end) ;
  else if( input == "eqv?" ) temp = eqv(root->d->r, level, d, end);
  else if( input == "equal?" ) temp = equ(root->d->r, level, d, end);
  else if( input == ">" ) temp = Greater(root->d, level, d, end);
	else if( input == ">=" ) temp = BigandEqual(root->d, level, d, end);
  else if( input == "<" ) temp = Smaller(root->d, level, d, end);
  else if( input == "<=" ) temp = SmallandEqual(root->d, level, d, end);
  else if( input == "=" ) temp = Equal(root->d, level, d, end);
  else if( input == "string-append" ) temp = string_append(root->d, level, d, end);
  else if( input == "string>?" ) temp = string_bigger(root->d, level, d, end);
  else if( input == "string<?" ) temp = string_smaller(root->d, level, d, end);
  else if( input == "string=?" ) temp = string_equal(root->d, level, d, end);
	else if( input == "string?" ) temp = str(root->d->r, level, d, end);
	else if( input == "null?" ) temp = null(root->d->r, level, d, end);
	else if( input == "boolean?" ) temp = boolean(root->d->r, level, d, end);
	else if( input == "pair?" ) temp = Pair(root->d->r, level, d, end);
  else if( input == "integer?" ) temp = Integer(root->d->r, level, d, end);
  else if( input == "real?" ) temp = Real(root->d->r, level, d, end);
  else if( input == "number?" ) temp = Number(root->d->r, level, d, end);
  else if( input == "symbol?" ) temp = Symbol(root->d->r, level, d, end);
  else if( input == "list?" ) temp = c_list(root->d->r, level, d, end);
  else if( input == "+" ) temp = Plus(root->d, level, d, end) ;
  else if( input == "-" ) temp = Minus(root->d, level, d, end);
  else if( input == "*" ) temp = Mult(root->d, level, d, end);
  else if( input == "/" ) temp = Div(root->d, level, d, end);
  else if( input == "not" ) temp = Not(root->d->r, level, d, end);
  else if( input == "begin" ) temp = Begin(root->d->r, level, d, end);
  else if( input == "atom?" ) temp = Atom(root->d->r, level, d, end);
  else if( input == "and" ) temp = And(root->d->r, level, d, end);
  else if( input == "or" ) temp = Or(root->d->r, level, d, end);
  return temp;
} // call() 

tree *eval( tree *root, int level, vector<def> &d, bool & exit ) {  //        

	if ( root->type == "INTEGER" ||  root->type == "FLOAT" || root->type == "STRING" || root->type == "NIL" || root->type == "T" ) {
		return root ;
	} // if
	else if ( root->type == "SYMBOL" ) {    
    root = getbind( root, d ) ;
    if ( root == NULL ) return NULL;
    return root;
	}  // else if
	else {    // s-exp root指向"(" 
    if ( !error( root, level, d, exit ) ) 
		  return NULL;
    tree *temp = new tree();
    temp = root->r ;
    root = call( root->d->str, root, level, d, exit ) ;
    if ( root == NULL ) return NULL;
    root->r = temp;
		return root;
	} // else
	
} // eval() 

void excute( vector<string> &input ) {
  int j = 0, index = 0, level = 0;
  vector<token> list ;
  vector<def> def;
  string exp, aaaaa ;
  token tk;
  bool end = false, stop = false, remain = false ;
  bool exit = false;
  tree *root = new tree();
  tree *temp = new tree();
  Add_Fuc( def ) ;
  for( int i = 0; i < input.size() && !end ; i++ ){
    j = 0;
    while ( input[i].size() > j && !end ) { //?P???h??s-exp 
    	if(Sexp( input, list, i, j, tk )){  // 語法沒問題 
    		line = i;
        column = j;
        modify( list );
	      Delnil( list );
	    	for ( int k = 0 ; k < list.size() ; k++){   //§?vector±???string 
	    	  if( k != list.size()-1 )
	    		  exp = exp + list[k].s + ' ';
	    	  else
	    		  exp = exp + list[k].s;
        } // for
				if ( exp != "" ) {
	        if ( list.size() == 1 ) {
	        	root = NULL;
	          root = new tree();
	          root->str = list[0].s;
	          root->type = Gettype( root->str );
	          
					} // if
					else {
					  exp = change(exp);  
            create( root, exp, index, stop, remain );
          } //建樹判斷evaluate文法 
	        temp = eval( root, level, def, end ) ;
	        if ( temp != NULL ) {
	        	cout << "> "; 
				    int x = 0;
				    bool sameline = false ;
				    print( temp, x, sameline );
				    cout << endl;
					} // if
				}  // if       
        stop = false;
        remain = false;
        index = 0;
        root = NULL;
        root = new tree(); 
        temp = new tree();
		  }  // if   	
    	else{   //  syntax error
    		line = i;
        column = j;
    	  if ( tk.s != "" ) // eof
		      cout << "> " << tk.errorline << endl << endl;
  			j = input[i].size();   // skip errorline	
		  } // else
    	list.clear();
    	exp.clear();
	  } // while 
	  
  } // for
  
  if (!end) cout << "> " << "ERROR (no more input) : END-OF-FILE encountered"<< endl  ;
} // excute()
 
int main() {
  string line = {"\0"};
  ifs.open("test1.txt");
  //ifs >> guTestNum;
  //ifs.get(); 
  vector<string> input ;
  vector<string> modify ;
  
  while( !ifs.eof() ) {	
    read( input );
  } // while
  cout << "Welcome to OurScheme!" << endl << endl;
  excute(input);
  cout << "Thanks for using OurScheme!";
  ifs.close();
    
} // main()
