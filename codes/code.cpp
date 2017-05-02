# include <bits/stdc++.h>
using namespace std;

# define isSkip(c) (c=='-' || c=='\t' || c=='\n' || c=='\r')
# define isLetter(c) ((c>='a' && c<='z') || (c>='A' && c<='Z'))
# define isNumber(c) (c>='0' && c<='9')
# define PB push_back

///Here will be stored the program
char buf[3000000];

///Vector with the reserved words
vector<string> reservedWords;

///Map asociating a particular token with its token name
map<string,string> tokenName;

///The current (possible) lexeme
string lexeme;

///The type of the token
string type;

///A list with all the error that appear in the analysis
vector < pair<int,int> > errorsList;

///Row and col in the current CHARACTER
int row,col;

///Row and col in the current TOKEN
int cR,cC;

///Current index
int i;

///Size of the program
int n;

///Number of errors in the analysis
int errors;

///Adds a char 'c' to the current lexeme
void add(char c);

///prints the current token
void printLex();

/**Finishes the current token and return the lector head (the index 'i') hm positions
PARAMETERS
int hm: the number characters that will be backtracked
string t: the type of the token
returns -1 (Always)
*/
int finish(int hm, string t);

/**Adds a error to the list and terminates the analysis procces on the current lexeme
by returning -1 as the next state for the FSM
returns -1 (Always)
*/
int error();

/**Impelments a Finite State Machine (FSM) which processes the program
PARAMETERS
    int state: the current state where the machine is
RETURNS
    int nextState: the next state (-1) if it has found a lexic error or a valid lexeme
*/
int alpha(int state);

/**Initialize:
    the reserved word in the language in vector reservedWords
    the name of the tokens given a symbol in map tokenName
    reads the input and set its size 'n'
    set i = 0
    set errors = 0
*/
void initialize();

/**Consume (advances the index i) if the character in the ith position is a ' ' or '\t' or '\n'
as multiple times as possible
*/
void consume();


/**The control program (main program)*/
int main();

class Token{
    private:
    string lexeme,type;
    int row,col;

    public:
    Token(string lex, string ty, int r, int c){
        lexeme = lex;
        type = ty;
        row = r;
        col = c;

        if(type.size()<=0) type = lexeme;
        else if(lexeme.size()<=0) lexeme = type;
    }

    friend ostream& operator<<(ostream& os, const Token & t){
        /*os<<"<";
        if(t.type.size()>0) os<<t.type<<",";
        if( t.lexeme.length()>0 && tokenName.find(t.lexeme) == tokenName.end() ) os<<t.lexeme<<",";
        os<<t.row<<","<<t.col<<">";*/

        os<<"lexema: "<<t.lexeme<<" tipo: "<<t.type<<" fila "<<t.row<<" columna "<<t.col;

        return os;
    }

    string getLexeme(){ return lexeme; }
    string getType(){ return type; }
    int getRow(){ return row; }
    int getCol(){ return col; }

};


vector<Token> tokens;


void add(char c){
    lexeme+=c;
}

void printLex(){

    /*cout<<"<";
    if(type.size()>0) cout<<type<<",";
    if( lexeme.length()>0 && tokenName.find(lexeme) == tokenName.end() ) cout<<lexeme<<",";
    cout<<cR+1<<","<<cC+1<<">"<<endl;*/
    tokens.push_back(Token(lexeme,type,cR+1,cC+1));

    lexeme = "";
    type = "";
}

int finish(int hm, string t){
     type = t;
     printLex();
     i-=hm;
     col-=hm;
     return -1;
}

int error(){
    errors++;
    errorsList.push_back(make_pair(cR+1,cC+1));
    type="";
    lexeme="";
    printf(">>> Error lexico(linea: %d, posicion: %d)\n",cR+1,cC+1);


    exit(0);

    return -1;
}

int alpha(int state){
    //consume();
    char c = buf[i++];
    col++;
    if(i>n+1){
        return -1;
    }

    switch(state){
        case 0:
            add(c);
            if( isNumber(c) ) return 3;
            if( isLetter(c) ) return 1;
            if( c== '"') return 9;
            if( c=='\'') return 11;
            if( c=='+' ){finish(0,tokenName["+"]); return -1;}
            if( c=='-' ){finish(0,tokenName["-"]); return -1;}
            if( c=='%' ){finish(0,tokenName["%"]); return -1;}
            if( c=='*' ){finish(0,tokenName["*"]); return -1;}
            if( c==';' ){finish(0,tokenName[";"]); return -1;}
            if( c==':' ){finish(0,tokenName[":"]); return -1;}
            if( c==',' ){finish(0,tokenName[","]); return -1;}
            if( c=='.' ){finish(0,tokenName["."]); return -1;}
            if( c=='(' ){finish(0,tokenName["("]); return -1;}
            if( c==')' ){finish(0,tokenName[")"]); return -1;}
            //if( c=='[' ){finish(0,tokenName["["]); return -1;}
            //if( c==']' ){finish(0,tokenName["]"]); return -1;}
            if( c== '/') return 16;
            if( c== '&') return 31;
            if( c=='<' ) return 22;
            if( c=='=' ) return 25;
            if( c=='>' ) return 28;
            if( c=='|' ) return 33;
            if( c=='!' ) return 35;
            else return error();
        break;

        case 1:
            if( isLetter(c) || c=='_' || isNumber(c) ){
                add(c);
                return 1;
            }
            else return 2;
        break;

        case 2:
            type = "";
            if( !binary_search( reservedWords.begin( ), reservedWords.end( ), lexeme ) )
                type = "id";

            printLex();
            i-=2;
            col-=2;

            return -1;
        break;

        case 3:
            if( isNumber(c) ){
                add(c);
                return 3;
            }else if(c=='.'){
                add(c);
                return 5;
            }else{
                return 4;
            }
        break;

        case 4:
            return finish(2,"tk_entero");
        break;

        case 5:
            if( isdigit(c)){
                add(c);
                return 7;
            }else{
                return 6;
            }
        break;

        case 6:
            if (lexeme.size () > 0)  lexeme.resize (lexeme.size () - 1);
            return finish(3,"tk_entero");
        break;

        case 7:
            if(isdigit(c)){
                add(c);
                return 7;
            }else{
                return 8;
            }
        break;

        case 8:
            return finish(2,"tk_real");
        break;

        case 9:
            add(c);
            if(c =='\n'){
            	int ret = lexeme.length()-1;
            	lexeme = "";
                return finish(ret,tokenName["\""]);
			}else if(c != '"'){
                return 9;
            }else{
                return 10;
            }
        break;

        case 10:
            return finish(1,"tk_cadena");
        break;

        case 11:
            add(c);
            if(c!='\''){
                return 12;
            }else{
                return 46;
            }
        break;

        case 12:
            if(c=='\''){
                add(c);
                return 46;
            }else{
                return 39;
            }
        break;

        case 16:
            if(c!='/' && c!='*') return finish(1,tokenName["/"]);
            else if(c=='*'){
                return 19;
            }else{
                return 18;
            }
        break;

        case 18:
            if(c=='\n'){
                row++;
                col=0;
                lexeme="";
                type = "";
                return -1;
            }else{
                return 18;
            }
        break;

        case 19:
            if(c!='*') {
                if(c=='\n'){
                    row++;
                    col=0;
                }
                return 19;
            }
            else return 20;
        break;

        case 20:
            if(c=='/'){
                lexeme="";
                type = "";
                return -1;
            }else{
                return 19;
            }
        break;

        case 22:
            if(c!='='){
                return finish(1,tokenName["<"]);
            }else{
                return finish(0,tokenName["<="]);
            }
        break;

        case 25:
            if(c=='='){
                 return finish(0,tokenName["=="]);
            }else{
                 return finish(1,tokenName["="]);
            }
        break;

        case 28:
            if(c!='='){
                return finish(1,tokenName[">"]);
            }else{
                return finish(0,tokenName[">="]);
            }
        break;

        case 31:
            if(c=='&'){
                add(c);
                return finish(0,tokenName["&&"]);
            }else{
                i--;
                col--;
                return error();
            }

        break;

        case 33:
            if(c=='|'){
                add(c);
                return finish(0,tokenName["||"]);
            }else{
                i--;
                col--;
                return error();
            }

        break;

        case 35:
            if(c=='='){
                add(c);
                return finish(0,tokenName["!="]);
            }else{
                return finish(1,tokenName["!"]);
            }
        break;

        case 39:
            type = "";
            if (lexeme.size () > 0)  lexeme.resize (lexeme.size () - 1);
            return finish(3,tokenName["'"]);
        break;

        case 46:
            return finish(1,"tk_caracter");
        break;

        default:
            return error();
        break;
    }
    return -1;
}

void initialize( ) {
    reservedWords.PB("booleano"); reservedWords.PB("caracter"); reservedWords.PB("entero"); reservedWords.PB("real"); reservedWords.PB("cadena");
    reservedWords.PB("leer"); reservedWords.PB("seleccionar"); reservedWords.PB("imprimir"); reservedWords.PB("si"); reservedWords.PB("entonces");
    reservedWords.PB("fin_si"); reservedWords.PB("si_no"); reservedWords.PB("mientras"); reservedWords.PB("verdadero"); reservedWords.PB("hacer");
    reservedWords.PB("fin_mientras"); reservedWords.PB("para"); reservedWords.PB("fin_para"); reservedWords.PB("entre"); reservedWords.PB("caso");
    reservedWords.PB("falso"); reservedWords.PB("romper"); reservedWords.PB("defecto"); reservedWords.PB("fin_seleccionar"); reservedWords.PB("estructura");
    reservedWords.PB("fin_estructura"); reservedWords.PB("retornar"); reservedWords.PB("fin_funcion"); reservedWords.PB("funcion_principal"); reservedWords.PB("funcion");
    reservedWords.PB("fin_principal");

    sort( reservedWords.begin( ), reservedWords.end( ) );

    tokenName["+"] = "tk_mas"; tokenName["-"] = "tk_menos"; tokenName["*"] = "tk_mult"; tokenName["/"] = "tk_div";
    tokenName["%"] = "tk_mod"; tokenName["="] = "tk_asig"; tokenName["<"] = "tk_menor"; tokenName[">"] = "tk_mayor";
    tokenName["<="] = "tk_menor_igual"; tokenName["||"] = "tk_o"; tokenName[">="] = "tk_mayor_igual"; tokenName["=="] = "tk_igual";
    tokenName["&&"] = "tk_y"; tokenName["!="] = "tk_dif"; tokenName["!"] = "tk_neg"; tokenName[":"] = "tk_dosp";
    tokenName["'"] = "tk_comilla_sen"; tokenName["\""] = "tk_comilla_dob"; tokenName[";"] = "tk_pyc"; tokenName[","] = "tk_coma";
    tokenName["("] = "tk_par_izq"; tokenName[")"] = "tk_par_der"; tokenName["."] = "tk_punto";

    i=0;
    n=0;
    errors=0;

    string s;

    while( getline(cin,s) ){
        for(int j=0 ; j<(int)s.length() ; j++){
            buf[n++] = s[j];
        }
        buf[n++]='\n';
    }
}

void consume(){
    while(isSkip(buf[i])){
        if(buf[i]=='\n'){
            row++;
            col=0;
        }else{
            col++;
        }
        i++;
    }
}

void getTokens(){
    initialize();
    int state = 0;
    while(i<=n){
        consume();
        cR=row; cC=col;
        if(i>=n) break;
        while( (state=alpha(state)) !=-1){

        }
        state=0;
    }
}

//ASD***************************************************

# define l token->getLexeme()
# define ty token->getType()
# define tn(a) tokenName[(a)]
# define vs vector<string>

void programa();

Token * token;
int indexOfToken = 0;

void errorSintaxis(vector<string> & vec){
    cout<<"Error de sintaxis, se esperaba: ";
    for(int i=0 ; i<(int)vec.size()-1 ; i++){
        cout<<vec[i]<<" , ";
    }
    cout<<vec[vec.size()-1]<<" pero se recibio "<<*token<<endl;
    exit(0);
}

void errorSintaxis(string a){
    vs aux;;
    aux.PB(a);
    errorSintaxis(aux);
}

void emparejar(string a){
    cout<<*token<<endl;
    if( token->getLexeme()==a || token->getType()==a ){
        indexOfToken++;
        token = &tokens[indexOfToken];
    }else{
        vector<string> aux;
        aux.PB(a);
        errorSintaxis(aux);
    }
}

int main(){
    freopen("lexer3.in","r",stdin);
    //freopen("lexer.out","w",stdout);
    getTokens();
    tokens.push_back(Token("EOF","",tokens[tokens.size()-1].getRow(),tokens[tokens.size()-1].getCol()+1));

    for(int i=0 ; i<(int)tokens.size() ; i++){
        cout<<tokens[i]<<endl;
    }
    token = &tokens[0];
    programa(); //Simbolo inicial

    if (token->getLexeme() != "EOF"){
        vector<string> aux;
        aux.PB("EOF");
        errorSintaxis(aux);
    }else{
        cout<<"Analisis terminado correctamente"<<endl;
    }
}


//FUNCIONES
void asignador();
void auxiliarCasos();
void auxiliarCasos2();
void auxiliarCasos3();
void auxiliarComando();
void auxiliarComando2();
void auxiliarExpresionBasica();
void auxiliarExpresionBasica2();
void cicloDoWhile();
void cicloPara();
void cicloWhile();
void comando();
void comandoDoWhile();
void comandos();
void comandosDoWhile();
void comandosDoWhileAux();
void condicional();
void declaracion();
void declaracion2();
void declaracion2Aux();
void declaracionFor();
void declaraciones();
void declaracionesExternas();
void declaracionesMultiples();
void elseNonTerminal();
void estructuraN();
void expresion();
void expresionAritmetica();
void expresionAritmetica1();
void expresionAritmetica1Aux();
void expresionAritmeticaAux();
void expresionAux();
void expresionBasica();
void expresionBooleana();
void expresionBooleanaAux();
void expresionRelacional();
void expresionRelacional1();
void expresionRelacional1Aux();
void expresionRelacional1Aux2();
void expresionRelacionalAux();
void expresionUnaria();
void funcionEspecial();
void funcionN();
void identificador();
void identificadorDeclaracion();
void identificadorEstructura();
void lexemaConcreto();
void opcionalRomper();
void parametros();
void parametrosMultiples();
void programa();
void seleccionador();
void tipo();
void tipo2();
void valores();
void valoresMultiples();
void asignador(){
	cout<<"asignador"<<endl;
	if( ty == "tk_coma" || ty == "tk_pyc"){
	}
	else if( ty == "tk_asig"){
		emparejar("tk_asig");
		expresion();
	}
	else {
		vs aux;
		aux.PB("tk_asig");
		aux.PB("tk_coma");
		aux.PB("tk_pyc");
		errorSintaxis(aux);
	}
}
void auxiliarCasos(){
	cout<<"auxiliarCasos"<<endl;
	if( ty == "caso"){
		emparejar("caso");
		lexemaConcreto();
		emparejar("tk_dosp");
		comandos();
		opcionalRomper();
		auxiliarCasos2();
	}
	else if( ty == "defecto"){
		auxiliarCasos3();
	}
	else {
		vs aux;
		aux.PB("caso");
		aux.PB("defecto");
		errorSintaxis(aux);
	}
}
void auxiliarCasos2(){
	cout<<"auxiliarCasos2"<<endl;
	if( ty == "caso"){
		emparejar("caso");
		lexemaConcreto();
		emparejar("tk_dosp");
		comandos();
		opcionalRomper();
		auxiliarCasos2();
	}
	else if( ty == "fin_seleccionar"){
	}
	else if( ty == "defecto"){
		auxiliarCasos3();
	}
	else {
		vs aux;
		aux.PB("caso");
		aux.PB("defecto");
		aux.PB("fin_seleccionar");
		errorSintaxis(aux);
	}
}
void auxiliarCasos3(){
	cout<<"auxiliarCasos3"<<endl;
	if( ty == "defecto"){
		emparejar("defecto");
		emparejar("tk_dosp");
		comandos();
		opcionalRomper();
	}
	else {
		vs aux;
		aux.PB("defecto");
		errorSintaxis(aux);
	}
}
void auxiliarComando(){
	cout<<"auxiliarComando"<<endl;
	if( ty == "id"){
		identificador();
		auxiliarComando2();
	}
	else {
		vs aux;
		aux.PB("id");
		errorSintaxis(aux);
	}
}
void auxiliarComando2(){
	cout<<"auxiliarComando2"<<endl;
	if( ty == "tk_par_izq"){
		emparejar("tk_par_izq");
		valores();
		emparejar("tk_par_der");
	}
	else if( ty == "tk_asig" || ty == "id"){
		declaracion2Aux();
	}
	else {
		vs aux;
		aux.PB("id");
		aux.PB("tk_asig");
		aux.PB("tk_par_izq");
		errorSintaxis(aux);
	}
}
void auxiliarExpresionBasica(){
	cout<<"auxiliarExpresionBasica"<<endl;
	if( ty == "id"){
		identificador();
		auxiliarExpresionBasica2();
	}
	else {
		vs aux;
		aux.PB("id");
		errorSintaxis(aux);
	}
}
void auxiliarExpresionBasica2(){
	cout<<"auxiliarExpresionBasica2"<<endl;
	if( ty == "tk_dif" || ty == "tk_mod" || ty == "tk_y" || ty == "tk_par_der" || ty == "tk_mult" || ty == "tk_mas" || ty == "tk_coma" || ty == "tk_menos" || ty == "tk_div" || ty == "tk_pyc" || ty == "tk_menor" || ty == "tk_menor_igual" || ty == "tk_igual" || ty == "tk_mayor" || ty == "tk_mayor_igual" || ty == "tk_o"){
	}
	else if( ty == "tk_par_izq"){
		emparejar("tk_par_izq");
		valores();
		emparejar("tk_par_der");
	}
	else {
		vs aux;
		aux.PB("tk_coma");
		aux.PB("tk_dif");
		aux.PB("tk_div");
		aux.PB("tk_igual");
		aux.PB("tk_mas");
		aux.PB("tk_mayor");
		aux.PB("tk_mayor_igual");
		aux.PB("tk_menor");
		aux.PB("tk_menor_igual");
		aux.PB("tk_menos");
		aux.PB("tk_mod");
		aux.PB("tk_mult");
		aux.PB("tk_o");
		aux.PB("tk_par_der");
		aux.PB("tk_par_izq");
		aux.PB("tk_pyc");
		aux.PB("tk_y");
		errorSintaxis(aux);
	}
}
void cicloDoWhile(){
	cout<<"cicloDoWhile"<<endl;
	if( ty == "hacer"){
		emparejar("hacer");
		comandosDoWhile();
	}
	else {
		vs aux;
		aux.PB("hacer");
		errorSintaxis(aux);
	}
}
void cicloPara(){
	cout<<"cicloPara"<<endl;
	if( ty == "para"){
		emparejar("para");
		emparejar("tk_par_izq");
		declaracionFor();
		emparejar("tk_pyc");
		expresion();
		emparejar("tk_pyc");
		expresionAritmetica1();
		emparejar("tk_par_der");
		emparejar("hacer");
		comandos();
		emparejar("fin_para");
	}
	else {
		vs aux;
		aux.PB("para");
		errorSintaxis(aux);
	}
}
void cicloWhile(){
	cout<<"cicloWhile"<<endl;
	if( ty == "mientras"){
		emparejar("mientras");
		emparejar("tk_par_izq");
		expresion();
		emparejar("tk_par_der");
		emparejar("hacer");
		comandos();
		emparejar("fin_mientras");
	}
	else {
		vs aux;
		aux.PB("mientras");
		errorSintaxis(aux);
	}
}
void comando(){
	cout<<"comando"<<endl;
	if( ty == "retornar"){
		emparejar("retornar");
		expresion();
		emparejar("tk_pyc");
	}
	else if( ty == "imprimir" || ty == "leer"){
		funcionEspecial();
	}
	else if( ty == "si"){
		condicional();
	}
	else if( ty == "booleano" || ty == "cadena" || ty == "caracter" || ty == "entero" || ty == "real"){
		declaracion2();
		emparejar("tk_pyc");
	}
	else if( ty == "mientras"){
		cicloWhile();
	}
	else if( ty == "hacer"){
		cicloDoWhile();
	}
	else if( ty == "para"){
		cicloPara();
	}
	else if( ty == "seleccionar"){
		seleccionador();
	}
	else if( ty == "id"){
		auxiliarComando();
		emparejar("tk_pyc");
	}
	else {
		vs aux;
		aux.PB("booleano");
		aux.PB("cadena");
		aux.PB("caracter");
		aux.PB("entero");
		aux.PB("hacer");
		aux.PB("id");
		aux.PB("imprimir");
		aux.PB("leer");
		aux.PB("mientras");
		aux.PB("para");
		aux.PB("real");
		aux.PB("retornar");
		aux.PB("seleccionar");
		aux.PB("si");
		errorSintaxis(aux);
	}
}
void comandoDoWhile(){
	cout<<"comandoDoWhile"<<endl;
	if( ty == "imprimir" || ty == "leer"){
		funcionEspecial();
	}
	else if( ty == "si"){
		condicional();
	}
	else if( ty == "booleano" || ty == "cadena" || ty == "caracter" || ty == "entero" || ty == "real"){
		declaracion2();
		emparejar("tk_pyc");
	}
	else if( ty == "hacer"){
		cicloDoWhile();
	}
	else if( ty == "para"){
		cicloPara();
	}
	else if( ty == "seleccionar"){
		seleccionador();
	}
	else if( ty == "id"){
		auxiliarComando();
		emparejar("tk_pyc");
	}
	else {
		vs aux;
		aux.PB("booleano");
		aux.PB("cadena");
		aux.PB("caracter");
		aux.PB("entero");
		aux.PB("hacer");
		aux.PB("id");
		aux.PB("imprimir");
		aux.PB("leer");
		aux.PB("para");
		aux.PB("real");
		aux.PB("seleccionar");
		aux.PB("si");
		errorSintaxis(aux);
	}
}
void comandos(){
	cout<<"comandos"<<endl;
	if( ty == "booleano" || ty == "cadena" || ty == "caracter" || ty == "entero" || ty == "hacer" || ty == "id" || ty == "imprimir" || ty == "leer" || ty == "mientras" || ty == "para" || ty == "real" || ty == "retornar" || ty == "seleccionar" || ty == "si"){
		comando();
		comandos();
	}
	else if( ty == "caso" || ty == "defecto" || ty == "fin_funcion" || ty == "fin_mientras" || ty == "fin_para" || ty == "fin_principal" || ty == "fin_seleccionar" || ty == "fin_si" || ty == "romper" || ty == "si_no"){
	}
	else {
		vs aux;
		aux.PB("booleano");
		aux.PB("cadena");
		aux.PB("caracter");
		aux.PB("caso");
		aux.PB("defecto");
		aux.PB("entero");
		aux.PB("fin_funcion");
		aux.PB("fin_mientras");
		aux.PB("fin_para");
		aux.PB("fin_principal");
		aux.PB("fin_seleccionar");
		aux.PB("fin_si");
		aux.PB("hacer");
		aux.PB("id");
		aux.PB("imprimir");
		aux.PB("leer");
		aux.PB("mientras");
		aux.PB("para");
		aux.PB("real");
		aux.PB("retornar");
		aux.PB("romper");
		aux.PB("seleccionar");
		aux.PB("si");
		aux.PB("si_no");
		errorSintaxis(aux);
	}
}
void comandosDoWhile(){
	cout<<"comandosDoWhile"<<endl;
	if( ty == "booleano" || ty == "cadena" || ty == "caracter" || ty == "entero" || ty == "hacer" || ty == "id" || ty == "imprimir" || ty == "leer" || ty == "para" || ty == "real" || ty == "seleccionar" || ty == "si"){
		comandoDoWhile();
		comandosDoWhile();
	}
	else if( ty == "mientras"){
		emparejar("mientras");
		emparejar("tk_par_izq");
		expresion();
		emparejar("tk_par_der");
		comandosDoWhileAux();
	}
	else {
		vs aux;
		aux.PB("booleano");
		aux.PB("cadena");
		aux.PB("caracter");
		aux.PB("entero");
		aux.PB("hacer");
		aux.PB("id");
		aux.PB("imprimir");
		aux.PB("leer");
		aux.PB("mientras");
		aux.PB("para");
		aux.PB("real");
		aux.PB("seleccionar");
		aux.PB("si");
		errorSintaxis(aux);
	}
}
void comandosDoWhileAux(){
	cout<<"comandosDoWhileAux"<<endl;
	if( ty == "tk_pyc"){
		emparejar("tk_pyc");
	}
	else if( ty == "hacer"){
		emparejar("hacer");
		comandos();
		emparejar("fin_mientras");
		comandosDoWhile();
	}
	else {
		vs aux;
		aux.PB("hacer");
		aux.PB("tk_pyc");
		errorSintaxis(aux);
	}
}
void condicional(){
	cout<<"condicional"<<endl;
	if( ty == "si"){
		emparejar("si");
		emparejar("tk_par_izq");
		expresion();
		emparejar("tk_par_der");
		emparejar("entonces");
		comandos();
		elseNonTerminal();
		emparejar("fin_si");
	}
	else {
		vs aux;
		aux.PB("si");
		errorSintaxis(aux);
	}
}
void declaracion(){
	cout<<"declaracion"<<endl;
	if( ty == "booleano" || ty == "cadena" || ty == "caracter" || ty == "entero" || ty == "id" || ty == "real"){
		tipo();
		identificadorDeclaracion();
		asignador();
		declaracionesMultiples();
		emparejar("tk_pyc");
	}
	else {
		vs aux;
		aux.PB("booleano");
		aux.PB("cadena");
		aux.PB("caracter");
		aux.PB("entero");
		aux.PB("id");
		aux.PB("real");
		errorSintaxis(aux);
	}
}
void declaracion2(){
	cout<<"declaracion2"<<endl;
	if( ty == "booleano" || ty == "cadena" || ty == "caracter" || ty == "entero" || ty == "real"){
		tipo2();
		identificadorDeclaracion();
		asignador();
		declaracionesMultiples();
	}
	else {
		vs aux;
		aux.PB("booleano");
		aux.PB("cadena");
		aux.PB("caracter");
		aux.PB("entero");
		aux.PB("real");
		errorSintaxis(aux);
	}
}
void declaracion2Aux(){
	cout<<"declaracion2Aux"<<endl;
	if( ty == "id"){
		identificadorDeclaracion();
		asignador();
		declaracionesMultiples();
	}
	else if( ty == "tk_asig"){
		emparejar("tk_asig");
		expresion();
	}
	else {
		vs aux;
		aux.PB("id");
		aux.PB("tk_asig");
		errorSintaxis(aux);
	}
}
void declaracionFor(){
	cout<<"declaracionFor"<<endl;
	if( ty == "booleano" || ty == "cadena" || ty == "caracter" || ty == "entero" || ty == "real"){
		declaracion2();
	}
	else if( ty == "id"){
		identificador();
		emparejar("tk_asig");
		expresion();
	}
	else {
		vs aux;
		aux.PB("booleano");
		aux.PB("cadena");
		aux.PB("caracter");
		aux.PB("entero");
		aux.PB("id");
		aux.PB("real");
		errorSintaxis(aux);
	}
}
void declaraciones(){
	cout<<"declaraciones"<<endl;
	if( ty == "booleano" || ty == "cadena" || ty == "caracter" || ty == "entero" || ty == "id" || ty == "real"){
		declaracion();
		declaraciones();
	}
	else if( ty == "fin_estructura"){
	}
	else {
		vs aux;
		aux.PB("booleano");
		aux.PB("cadena");
		aux.PB("caracter");
		aux.PB("entero");
		aux.PB("fin_estructura");
		aux.PB("id");
		aux.PB("real");
		errorSintaxis(aux);
	}
}
void declaracionesExternas(){
	cout<<"declaracionesExternas"<<endl;
	if( ty == "funcion"){
		funcionN();
		declaracionesExternas();
	}
	else if( ty == "estructura"){
		estructuraN();
		declaracionesExternas();
	}
	else if( ty == "booleano" || ty == "cadena" || ty == "caracter" || ty == "entero" || ty == "id" || ty == "real"){
		declaracion();
		declaracionesExternas();
	}
	else if( ty == "EOF" || ty == "funcion_principal"){
	}
	else {
		vs aux;
		aux.PB("EOF");
		aux.PB("booleano");
		aux.PB("cadena");
		aux.PB("caracter");
		aux.PB("entero");
		aux.PB("estructura");
		aux.PB("funcion");
		aux.PB("funcion_principal");
		aux.PB("id");
		aux.PB("real");
		errorSintaxis(aux);
	}
}
void declaracionesMultiples(){
	cout<<"declaracionesMultiples"<<endl;
	if( ty == "tk_coma"){
		emparejar("tk_coma");
		identificadorDeclaracion();
		asignador();
		declaracionesMultiples();
	}
	else if( ty == "tk_pyc"){
	}
	else {
		vs aux;
		aux.PB("tk_coma");
		aux.PB("tk_pyc");
		errorSintaxis(aux);
	}
}
void elseNonTerminal(){
	cout<<"elseNonTerminal"<<endl;
	if( ty == "si_no"){
		emparejar("si_no");
		comandos();
	}
	else if( ty == "fin_si"){
	}
	else {
		vs aux;
		aux.PB("fin_si");
		aux.PB("si_no");
		errorSintaxis(aux);
	}
}
void estructuraN(){
	cout<<"estructuraN"<<endl;
	if( ty == "estructura"){
		emparejar("estructura");
		identificadorDeclaracion();
		declaraciones();
		emparejar("fin_estructura");
	}
	else {
		vs aux;
		aux.PB("estructura");
		errorSintaxis(aux);
	}
}
void expresion(){
	cout<<"expresion"<<endl;
	if( ty == "tk_neg" || ty == "tk_par_izq" || ty == "tk_menos" || ty == "falso" || ty == "id" || ty == "tk_cadena" || ty == "tk_caracter" || ty == "tk_entero" || ty == "tk_real" || ty == "verdadero"){
		expresionBooleana();
		expresionAux();
	}
	else {
		vs aux;
		aux.PB("falso");
		aux.PB("id");
		aux.PB("tk_cadena");
		aux.PB("tk_caracter");
		aux.PB("tk_entero");
		aux.PB("tk_menos");
		aux.PB("tk_neg");
		aux.PB("tk_par_izq");
		aux.PB("tk_real");
		aux.PB("verdadero");
		errorSintaxis(aux);
	}
}
void expresionAritmetica(){
	cout<<"expresionAritmetica"<<endl;
	if( ty == "tk_neg" || ty == "tk_par_izq" || ty == "tk_menos" || ty == "falso" || ty == "id" || ty == "tk_caracter" || ty == "tk_entero" || ty == "tk_real" || ty == "verdadero"){
		expresionUnaria();
		expresionAritmeticaAux();
	}
	else {
		vs aux;
		aux.PB("falso");
		aux.PB("id");
		aux.PB("tk_caracter");
		aux.PB("tk_entero");
		aux.PB("tk_menos");
		aux.PB("tk_neg");
		aux.PB("tk_par_izq");
		aux.PB("tk_real");
		aux.PB("verdadero");
		errorSintaxis(aux);
	}
}
void expresionAritmetica1(){
	cout<<"expresionAritmetica1"<<endl;
	if( ty == "tk_neg" || ty == "tk_par_izq" || ty == "tk_menos" || ty == "falso" || ty == "id" || ty == "tk_caracter" || ty == "tk_entero" || ty == "tk_real" || ty == "verdadero"){
		expresionAritmetica();
		expresionAritmetica1Aux();
	}
	else {
		vs aux;
		aux.PB("falso");
		aux.PB("id");
		aux.PB("tk_caracter");
		aux.PB("tk_entero");
		aux.PB("tk_menos");
		aux.PB("tk_neg");
		aux.PB("tk_par_izq");
		aux.PB("tk_real");
		aux.PB("verdadero");
		errorSintaxis(aux);
	}
}
void expresionAritmetica1Aux(){
	cout<<"expresionAritmetica1Aux"<<endl;
	if( ty == "tk_mas"){
		emparejar("tk_mas");
		expresionAritmetica1();
	}
	else if( ty == "tk_menos"){
		emparejar("tk_menos");
		expresionAritmetica1();
	}
	else if( ty == "tk_dif" || ty == "tk_y" || ty == "tk_par_der" || ty == "tk_coma" || ty == "tk_pyc" || ty == "tk_menor" || ty == "tk_menor_igual" || ty == "tk_igual" || ty == "tk_mayor" || ty == "tk_mayor_igual" || ty == "tk_o"){
	}
	else {
		vs aux;
		aux.PB("tk_coma");
		aux.PB("tk_dif");
		aux.PB("tk_igual");
		aux.PB("tk_mas");
		aux.PB("tk_mayor");
		aux.PB("tk_mayor_igual");
		aux.PB("tk_menor");
		aux.PB("tk_menor_igual");
		aux.PB("tk_menos");
		aux.PB("tk_o");
		aux.PB("tk_par_der");
		aux.PB("tk_pyc");
		aux.PB("tk_y");
		errorSintaxis(aux);
	}
}
void expresionAritmeticaAux(){
	cout<<"expresionAritmeticaAux"<<endl;
	if( ty == "tk_mult"){
		emparejar("tk_mult");
		expresionAritmetica();
	}
	else if( ty == "tk_div"){
		emparejar("tk_div");
		expresionAritmetica();
	}
	else if( ty == "tk_mod"){
		emparejar("tk_mod");
		expresionAritmetica();
	}
	else if( ty == "tk_dif" || ty == "tk_y" || ty == "tk_par_der" || ty == "tk_mas" || ty == "tk_coma" || ty == "tk_menos" || ty == "tk_pyc" || ty == "tk_menor" || ty == "tk_menor_igual" || ty == "tk_igual" || ty == "tk_mayor" || ty == "tk_mayor_igual" || ty == "tk_o"){
	}
	else {
		vs aux;
		aux.PB("tk_coma");
		aux.PB("tk_dif");
		aux.PB("tk_div");
		aux.PB("tk_igual");
		aux.PB("tk_mas");
		aux.PB("tk_mayor");
		aux.PB("tk_mayor_igual");
		aux.PB("tk_menor");
		aux.PB("tk_menor_igual");
		aux.PB("tk_menos");
		aux.PB("tk_mod");
		aux.PB("tk_mult");
		aux.PB("tk_o");
		aux.PB("tk_par_der");
		aux.PB("tk_pyc");
		aux.PB("tk_y");
		errorSintaxis(aux);
	}
}
void expresionAux(){
	cout<<"expresionAux"<<endl;
	if( ty == "tk_o"){
		emparejar("tk_o");
		expresion();
	}
	else if( ty == "tk_par_der" || ty == "tk_coma" || ty == "tk_pyc"){
	}
	else {
		vs aux;
		aux.PB("tk_coma");
		aux.PB("tk_o");
		aux.PB("tk_par_der");
		aux.PB("tk_pyc");
		errorSintaxis(aux);
	}
}
void expresionBasica(){
	cout<<"expresionBasica"<<endl;
	if( ty == "tk_entero"){
		emparejar("tk_entero");
	}
	else if( ty == "tk_real"){
		emparejar("tk_real");
	}
	else if( ty == "tk_caracter"){
		emparejar("tk_caracter");
	}
	else if( ty == "verdadero"){
		emparejar("verdadero");
	}
	else if( ty == "falso"){
		emparejar("falso");
	}
	else if( ty == "tk_par_izq"){
		emparejar("tk_par_izq");
		expresion();
		emparejar("tk_par_der");
	}
	else if( ty == "id"){
		auxiliarExpresionBasica();
	}
	else {
		vs aux;
		aux.PB("falso");
		aux.PB("id");
		aux.PB("tk_caracter");
		aux.PB("tk_entero");
		aux.PB("tk_par_izq");
		aux.PB("tk_real");
		aux.PB("verdadero");
		errorSintaxis(aux);
	}
}
void expresionBooleana(){
	cout<<"expresionBooleana"<<endl;
	if( ty == "tk_neg" || ty == "tk_par_izq" || ty == "tk_menos" || ty == "falso" || ty == "id" || ty == "tk_cadena" || ty == "tk_caracter" || ty == "tk_entero" || ty == "tk_real" || ty == "verdadero"){
		expresionRelacional1();
		expresionBooleanaAux();
	}
	else {
		vs aux;
		aux.PB("falso");
		aux.PB("id");
		aux.PB("tk_cadena");
		aux.PB("tk_caracter");
		aux.PB("tk_entero");
		aux.PB("tk_menos");
		aux.PB("tk_neg");
		aux.PB("tk_par_izq");
		aux.PB("tk_real");
		aux.PB("verdadero");
		errorSintaxis(aux);
	}
}
void expresionBooleanaAux(){
	cout<<"expresionBooleanaAux"<<endl;
	if( ty == "tk_y"){
		emparejar("tk_y");
		expresionBooleana();
	}
	else if( ty == "tk_par_der" || ty == "tk_coma" || ty == "tk_pyc" || ty == "tk_o"){
	}
	else {
		vs aux;
		aux.PB("tk_coma");
		aux.PB("tk_o");
		aux.PB("tk_par_der");
		aux.PB("tk_pyc");
		aux.PB("tk_y");
		errorSintaxis(aux);
	}
}
void expresionRelacional(){
	cout<<"expresionRelacional"<<endl;
	if( ty == "tk_neg" || ty == "tk_par_izq" || ty == "tk_menos" || ty == "falso" || ty == "id" || ty == "tk_caracter" || ty == "tk_entero" || ty == "tk_real" || ty == "verdadero"){
		expresionAritmetica1();
		expresionRelacionalAux();
	}
	else {
		vs aux;
		aux.PB("falso");
		aux.PB("id");
		aux.PB("tk_caracter");
		aux.PB("tk_entero");
		aux.PB("tk_menos");
		aux.PB("tk_neg");
		aux.PB("tk_par_izq");
		aux.PB("tk_real");
		aux.PB("verdadero");
		errorSintaxis(aux);
	}
}
void expresionRelacional1(){
	cout<<"expresionRelacional1"<<endl;
	if( ty == "tk_neg" || ty == "tk_par_izq" || ty == "tk_menos" || ty == "falso" || ty == "id" || ty == "tk_caracter" || ty == "tk_entero" || ty == "tk_real" || ty == "verdadero"){
		expresionRelacional();
		expresionRelacional1Aux();
	}
	else if( ty == "tk_cadena"){
		emparejar("tk_cadena");
		expresionRelacional1Aux2();
	}
	else {
		vs aux;
		aux.PB("falso");
		aux.PB("id");
		aux.PB("tk_cadena");
		aux.PB("tk_caracter");
		aux.PB("tk_entero");
		aux.PB("tk_menos");
		aux.PB("tk_neg");
		aux.PB("tk_par_izq");
		aux.PB("tk_real");
		aux.PB("verdadero");
		errorSintaxis(aux);
	}
}
void expresionRelacional1Aux(){
	cout<<"expresionRelacional1Aux"<<endl;
	if( ty == "tk_igual"){
		emparejar("tk_igual");
		expresionRelacional1();
	}
	else if( ty == "tk_dif"){
		emparejar("tk_dif");
		expresionRelacional1();
	}
	else if( ty == "tk_y" || ty == "tk_par_der" || ty == "tk_coma" || ty == "tk_pyc" || ty == "tk_o"){
	}
	else {
		vs aux;
		aux.PB("tk_coma");
		aux.PB("tk_dif");
		aux.PB("tk_igual");
		aux.PB("tk_o");
		aux.PB("tk_par_der");
		aux.PB("tk_pyc");
		aux.PB("tk_y");
		errorSintaxis(aux);
	}
}
void expresionRelacional1Aux2(){
	cout<<"expresionRelacional1Aux2"<<endl;
	if( ty == "tk_igual"){
		emparejar("tk_igual");
		emparejar("tk_cadena");
	}
	else if( ty == "tk_dif"){
		emparejar("tk_dif");
		emparejar("tk_cadena");
	}
	else if( ty == "tk_y" || ty == "tk_par_der" || ty == "tk_coma" || ty == "tk_pyc" || ty == "tk_o"){
	}
	else {
		vs aux;
		aux.PB("tk_coma");
		aux.PB("tk_dif");
		aux.PB("tk_igual");
		aux.PB("tk_o");
		aux.PB("tk_par_der");
		aux.PB("tk_pyc");
		aux.PB("tk_y");
		errorSintaxis(aux);
	}
}
void expresionRelacionalAux(){
	cout<<"expresionRelacionalAux"<<endl;
	if( ty == "tk_menor"){
		emparejar("tk_menor");
		expresionRelacional();
	}
	else if( ty == "tk_menor_igual"){
		emparejar("tk_menor_igual");
		expresionRelacional();
	}
	else if( ty == "tk_mayor"){
		emparejar("tk_mayor");
		expresionRelacional();
	}
	else if( ty == "tk_mayor_igual"){
		emparejar("tk_mayor_igual");
		expresionRelacional();
	}
	else if( ty == "tk_dif" || ty == "tk_y" || ty == "tk_par_der" || ty == "tk_coma" || ty == "tk_pyc" || ty == "tk_igual" || ty == "tk_o"){
	}
	else {
		vs aux;
		aux.PB("tk_coma");
		aux.PB("tk_dif");
		aux.PB("tk_igual");
		aux.PB("tk_mayor");
		aux.PB("tk_mayor_igual");
		aux.PB("tk_menor");
		aux.PB("tk_menor_igual");
		aux.PB("tk_o");
		aux.PB("tk_par_der");
		aux.PB("tk_pyc");
		aux.PB("tk_y");
		errorSintaxis(aux);
	}
}
void expresionUnaria(){
	cout<<"expresionUnaria"<<endl;
	if( ty == "tk_neg"){
		emparejar("tk_neg");
		expresionBasica();
	}
	else if( ty == "tk_menos"){
		emparejar("tk_menos");
		expresionBasica();
	}
	else if( ty == "tk_par_izq" || ty == "falso" || ty == "id" || ty == "tk_caracter" || ty == "tk_entero" || ty == "tk_real" || ty == "verdadero"){
		expresionBasica();
	}
	else {
		vs aux;
		aux.PB("falso");
		aux.PB("id");
		aux.PB("tk_caracter");
		aux.PB("tk_entero");
		aux.PB("tk_menos");
		aux.PB("tk_neg");
		aux.PB("tk_par_izq");
		aux.PB("tk_real");
		aux.PB("verdadero");
		errorSintaxis(aux);
	}
}
void funcionEspecial(){
	cout<<"funcionEspecial"<<endl;
	if( ty == "imprimir"){
		emparejar("imprimir");
		emparejar("tk_par_izq");
		valores();
		emparejar("tk_par_der");
		emparejar("tk_pyc");
	}
	else if( ty == "leer"){
		emparejar("leer");
		emparejar("tk_par_izq");
		identificador();
		emparejar("tk_par_der");
		emparejar("tk_pyc");
	}
	else {
		vs aux;
		aux.PB("imprimir");
		aux.PB("leer");
		errorSintaxis(aux);
	}
}
void funcionN(){
	cout<<"funcionN"<<endl;
	if( ty == "funcion"){
		emparejar("funcion");
		tipo();
		identificadorDeclaracion();
		emparejar("tk_par_izq");
		parametros();
		emparejar("tk_par_der");
		emparejar("hacer");
		comandos();
		emparejar("fin_funcion");
	}
	else {
		vs aux;
		aux.PB("funcion");
		errorSintaxis(aux);
	}
}
void identificador(){
	cout<<"identificador"<<endl;
	if( ty == "id"){
		emparejar("id");
		identificadorEstructura();
	}
	else {
		vs aux;
		aux.PB("id");
		errorSintaxis(aux);
	}
}
void identificadorDeclaracion(){
	cout<<"identificadorDeclaracion"<<endl;
	if( ty == "id"){
		emparejar("id");
	}
	else {
		vs aux;
		aux.PB("id");
		errorSintaxis(aux);
	}
}
void identificadorEstructura(){
	cout<<"identificadorEstructura"<<endl;
	if( ty == "tk_punto"){
		emparejar("tk_punto");
		emparejar("id");
		identificadorEstructura();
	}
	else if( ty == "tk_dif" || ty == "tk_mod" || ty == "tk_y" || ty == "tk_par_izq" || ty == "tk_par_der" || ty == "tk_mult" || ty == "tk_mas" || ty == "tk_coma" || ty == "tk_menos" || ty == "tk_div" || ty == "tk_pyc" || ty == "tk_menor" || ty == "tk_menor_igual" || ty == "tk_asig" || ty == "tk_igual" || ty == "tk_mayor" || ty == "tk_mayor_igual" || ty == "id" || ty == "tk_o"){
	}
	else {
		vs aux;
		aux.PB("id");
		aux.PB("tk_asig");
		aux.PB("tk_coma");
		aux.PB("tk_dif");
		aux.PB("tk_div");
		aux.PB("tk_igual");
		aux.PB("tk_mas");
		aux.PB("tk_mayor");
		aux.PB("tk_mayor_igual");
		aux.PB("tk_menor");
		aux.PB("tk_menor_igual");
		aux.PB("tk_menos");
		aux.PB("tk_mod");
		aux.PB("tk_mult");
		aux.PB("tk_o");
		aux.PB("tk_par_der");
		aux.PB("tk_par_izq");
		aux.PB("tk_punto");
		aux.PB("tk_pyc");
		aux.PB("tk_y");
		errorSintaxis(aux);
	}
}
void lexemaConcreto(){
	cout<<"lexemaConcreto"<<endl;
	if( ty == "tk_entero"){
		emparejar("tk_entero");
	}
	else if( ty == "tk_real"){
		emparejar("tk_real");
	}
	else if( ty == "tk_cadena"){
		emparejar("tk_cadena");
	}
	else if( ty == "tk_caracter"){
		emparejar("tk_caracter");
	}
	else if( ty == "verdadero"){
		emparejar("verdadero");
	}
	else if( ty == "falso"){
		emparejar("falso");
	}
	else {
		vs aux;
		aux.PB("falso");
		aux.PB("tk_cadena");
		aux.PB("tk_caracter");
		aux.PB("tk_entero");
		aux.PB("tk_real");
		aux.PB("verdadero");
		errorSintaxis(aux);
	}
}
void opcionalRomper(){
	cout<<"opcionalRomper"<<endl;
	if( ty == "caso" || ty == "defecto" || ty == "fin_seleccionar"){
	}
	else if( ty == "romper"){
		emparejar("romper");
		emparejar("tk_pyc");
	}
	else {
		vs aux;
		aux.PB("caso");
		aux.PB("defecto");
		aux.PB("fin_seleccionar");
		aux.PB("romper");
		errorSintaxis(aux);
	}
}
void parametros(){
	cout<<"parametros"<<endl;
	if( ty == "booleano" || ty == "cadena" || ty == "caracter" || ty == "entero" || ty == "id" || ty == "real"){
		tipo();
		identificadorDeclaracion();
		parametrosMultiples();
	}
	else if( ty == "tk_par_der"){
	}
	else {
		vs aux;
		aux.PB("booleano");
		aux.PB("cadena");
		aux.PB("caracter");
		aux.PB("entero");
		aux.PB("id");
		aux.PB("real");
		aux.PB("tk_par_der");
		errorSintaxis(aux);
	}
}
void parametrosMultiples(){
	cout<<"parametrosMultiples"<<endl;
	if( ty == "tk_coma"){
		emparejar("tk_coma");
		tipo();
		identificadorDeclaracion();
		parametrosMultiples();
	}
	else if( ty == "tk_par_der"){
	}
	else {
		vs aux;
		aux.PB("tk_coma");
		aux.PB("tk_par_der");
		errorSintaxis(aux);
	}
}
void programa(){
	cout<<"programa"<<endl;
	if( ty == "booleano" || ty == "cadena" || ty == "caracter" || ty == "entero" || ty == "estructura" || ty == "funcion" || ty == "funcion_principal" || ty == "id" || ty == "real"){
		declaracionesExternas();
		emparejar("funcion_principal");
		comandos();
		emparejar("fin_principal");
		declaracionesExternas();
	}
	else {
		vs aux;
		aux.PB("booleano");
		aux.PB("cadena");
		aux.PB("caracter");
		aux.PB("entero");
		aux.PB("estructura");
		aux.PB("funcion");
		aux.PB("funcion_principal");
		aux.PB("id");
		aux.PB("real");
		errorSintaxis(aux);
	}
}
void seleccionador(){
	cout<<"seleccionador"<<endl;
	if( ty == "seleccionar"){
		emparejar("seleccionar");
		emparejar("tk_par_izq");
		identificador();
		emparejar("tk_par_der");
		emparejar("entre");
		auxiliarCasos();
		emparejar("fin_seleccionar");
	}
	else {
		vs aux;
		aux.PB("seleccionar");
		errorSintaxis(aux);
	}
}
void tipo(){
	cout<<"tipo"<<endl;
	if( ty == "booleano"){
		emparejar("booleano");
	}
	else if( ty == "entero"){
		emparejar("entero");
	}
	else if( ty == "real"){
		emparejar("real");
	}
	else if( ty == "cadena"){
		emparejar("cadena");
	}
	else if( ty == "caracter"){
		emparejar("caracter");
	}
	else if( ty == "id"){
		identificadorDeclaracion();
	}
	else {
		vs aux;
		aux.PB("booleano");
		aux.PB("cadena");
		aux.PB("caracter");
		aux.PB("entero");
		aux.PB("id");
		aux.PB("real");
		errorSintaxis(aux);
	}
}
void tipo2(){
	cout<<"tipo2"<<endl;
	if( ty == "booleano"){
		emparejar("booleano");
	}
	else if( ty == "entero"){
		emparejar("entero");
	}
	else if( ty == "real"){
		emparejar("real");
	}
	else if( ty == "cadena"){
		emparejar("cadena");
	}
	else if( ty == "caracter"){
		emparejar("caracter");
	}
	else {
		vs aux;
		aux.PB("booleano");
		aux.PB("cadena");
		aux.PB("caracter");
		aux.PB("entero");
		aux.PB("real");
		errorSintaxis(aux);
	}
}
void valores(){
	cout<<"valores"<<endl;
	if( ty == "tk_neg" || ty == "tk_par_izq" || ty == "tk_menos" || ty == "falso" || ty == "id" || ty == "tk_cadena" || ty == "tk_caracter" || ty == "tk_entero" || ty == "tk_real" || ty == "verdadero"){
		expresion();
		valoresMultiples();
	}
	else if( ty == "tk_par_der"){
	}
	else {
		vs aux;
		aux.PB("falso");
		aux.PB("id");
		aux.PB("tk_cadena");
		aux.PB("tk_caracter");
		aux.PB("tk_entero");
		aux.PB("tk_menos");
		aux.PB("tk_neg");
		aux.PB("tk_par_der");
		aux.PB("tk_par_izq");
		aux.PB("tk_real");
		aux.PB("verdadero");
		errorSintaxis(aux);
	}
}
void valoresMultiples(){
	cout<<"valoresMultiples"<<endl;
	if( ty == "tk_coma"){
		emparejar("tk_coma");
		expresion();
		valoresMultiples();
	}
	else if( ty == "tk_par_der"){
	}
	else {
		vs aux;
		aux.PB("tk_coma");
		aux.PB("tk_par_der");
		errorSintaxis(aux);
	}
}