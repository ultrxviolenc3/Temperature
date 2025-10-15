#include <iostream>
#include <fstream>
using namespace std;

class temperature{
	
	double temper;
	char scale;
	
	public:
	
	temperature(double t=0.0, char s='C') : temper(t), scale(s) {}
	 void set(double t, char s)  { temper=t; scale=s; }
	 
	double toC() { 
		
		if( scale == 'C' ) return temper ;
		else if ( scale == 'K' ) return temper - 273.15;
		return (temper - 32.0) / 1.8 ; //F
		}
	
       void print()  {
        cout<<"("<<temper<<", "<<scale<<")";
    }
    
    double gettemper() { 
		return temper; 
		}
		
    char getscale() {
		 return scale; 
		 }
	
	};
	
	class table {
		
		 int numstrok;
		 int numstolb;
		temperature** temp;
		
		public:
		table( int n = 0,  int k =0) : numstrok(n), numstolb(k), temp(nullptr)
		{ 
			if(n > 0 && k > 0) {
			
				temp=new (nothrow) temperature*[n];
				if(!temp)
				{
					cout<<"Ошибка выделения памяти"<<endl;
					return;
					}
				for(int i=0; i<n; i++)
			{
			  temp[i] = new (nothrow) temperature[k];
				  if (!temp[i]) {
                cout << "Ошибка выделение памяти"<< endl;
                for ( int j = 0; j < i; j++) {
                   delete[] temp[j];
				     }
				       delete[] temp;
                   temp = nullptr;
                     numstolb=0;
                     numstrok=0;
                     return; 
				}
				
			   } 
			} 
		}
		
		table(const table& other) ///konst kop
		{ 
    numstrok = other.numstrok;
    numstolb = other.numstolb;

    if (numstrok > 0 && numstolb > 0) {
        temp = new(nothrow) temperature*[numstrok];
        if(!temp){
			cout << "Ошибка выделение памяти"<< endl;
			}
        for ( int i = 0; i < numstrok; i++) {
            temp[i] = new(nothrow) temperature[numstolb];
            if(!temp[i]){
				cout << "Ошибка выделение памяти"<< endl;
				}
            for ( int j = 0; j < numstolb; j++) {
                temp[i][j] = other.temp[i][j]; 
            }
        }
    } else {
        temp = nullptr;
            }
       }
       
       table& operator=(const table& other) {
    if (this == &other) return *this;

    if (temp) {
        for (int i = 0; i < numstrok; i++) delete[] temp[i];
        delete[] temp;
    }

    numstrok = other.numstrok;
    numstolb = other.numstolb;

    if (numstrok && numstolb) {
        temp = new(nothrow) temperature*[numstrok];
        if(!temp){
			cout<<"Ошибка выделения памяти"<<endl;
			}
        for ( int i = 0; i < numstrok; i++) {
            temp[i] = new(nothrow) temperature[numstolb];
            if(!temp[i]){
				cout<<"Ошибка выделения памяти"<<endl;
				}
            for (int j = 0; j < numstolb; j++)
                temp[i][j] = other.temp[i][j];
        }
    } else {
        temp = nullptr;
    }
    return *this;
}

	bool sredn(int strok, double* result) {
    
    if (strok >= numstrok || strok<0) {
        cout << "Ошибка такой строки нет!"<< endl;
        return false;
    }

    double sum = 0;
    for (int i = 0; i < numstolb; i++)
        sum += temp[strok][i].toC();

    *result = sum / numstolb;  
    return true;              
}

		
		bool min_in_strok( int strok, double* minimum) { 
    if (!minimum) return false;
    
    if (strok >= numstrok || strok<0) {
        cout << "Ошибка неверный номер строки" << endl;
        return false;
    }
    double tmin= temp[strok][0].toC();
    for (int i = 1; i < numstolb; i++) {
        double val = temp[strok][i].toC();
        if (val < tmin) tmin = val;
    }
    *minimum = tmin;
    return true;
}
  
  bool maxtable(double* maximum) {  
    if (!maximum) return false;
    double max = temp[0][0].toC();
    for ( int i = 0; i < numstrok; i++) {
        for ( int j = 0; j < numstolb; j++) {
            double val = temp[i][j].toC();
            if (val > max) max = val;
        }
    }
    *maximum = max;
    return true;
}
table operator+(const table& other) { ///peregruzka
    if (numstrok != other.numstrok || numstolb != other.numstolb) {
        cout << "Ошибка таблицы разных размеров сложение невозможно!" << endl;
        return table(); 
    }

    table result(numstrok, numstolb);

    for ( int i = 0; i < numstrok; i++) {
        for ( int j = 0; j < numstolb; j++) {
    
            double valt1 = temp[i][j].gettemper();
            char   sct1 = temp[i][j].getscale();
            double valt2 = other.temp[i][j].gettemper();
            char   sct2 = other.temp[i][j].getscale();

            double valt2sct1;
            if (sct1 == sct2) {
                valt2sct1 = valt2; 
            } else {
                double valt2C = (sct2=='C') ? valt2 : (sct2=='K') ? (valt2 - 273.15)  : (valt2 - 32.0) / 1.8; 
              
                valt2sct1 = (sct1=='C') ? valt2C  : (sct1=='K') ? (valt2C + 273.15)  : (valt2C * 1.8 + 32.0);  
            }

            double sum = valt1 + valt2sct1;           
            result.temp[i][j].set(sum, sct1);       
        }
    }
    return result;
}
  
		~table() {
			
			if(temp)
			{
				for( int i = 0;i<numstrok;i++)
				delete[] temp[i];
				delete[] temp;
				}
			}
		 bool readFromFile(const string& filename) {
        ifstream fin(filename);
        if (!fin.is_open()) {
            cout << "Ошибка при открытии файла "  << endl;
            return false;
        }
        int tnumstrok,tnumstolb;
        if (!(fin >> tnumstrok >> tnumstolb)) {
        cout << "Ошибка не удалось прочитать размеры таблицы"<<endl;
        return false;
    }
        
        if (tnumstrok <= 0 || tnumstolb <= 0) {
        cout << "Ошибка неверные размеры таблицы" << endl;
        return false;
    }
    if (temp) {
    for ( int i = 0; i < numstrok; i++)
        delete[] temp[i];
    delete[] temp;
    temp = nullptr;
}

       numstrok = tnumstrok;
       numstolb = tnumstolb;
        temp = new (nothrow) temperature*[numstrok];
          if (!temp) {
        cout << "Ошибка выделения памяти" << endl;
        return false;
    }
        for ( int i = 0; i < numstrok; i++){
            temp[i] = new (nothrow) temperature[numstolb];
         if (!temp[i]) {
           cout << "Ошибка выделения памяти " << endl;
            temp = nullptr;
            numstolb=0;
            numstrok=0;
        return false;
    
    }
   } 
    for (int i = 0; i < numstrok; i++) {
        for (int j = 0; j < numstolb; j++) {
            double val;
            char sc;

            if (!(fin >> val >> sc)) {
                if (fin.eof()) {
                    cout << "Ошибка в файле меньше данных чем указано размерами таблицы!" << endl;
                } else {
                    cout << "Ошибка неверный формат данных в ячейке" << endl;
                }
                return false;
            }
            if (sc != 'C' && sc != 'K' && sc != 'F') {
                cout << "Ошибка неизвестная шкала " << endl;
                return false;
            }

            if (sc == 'K' && val <= 0) {
                cout << "Ошибка температура не имеет физического смысла" << endl;
                return false;
            }
            if (sc == 'C' && val <=-273.15) {
          cout << "Ошибка температура не имеет физического смысла"<<endl;
    return false;
}
       if (sc == 'F' && val <= -459.67) {
    cout << "Ошибка температура не имеет физического смысла"<<endl;
    return false;
                   }
            temp[i][j].set(val, sc);
        }
    }
      double dopval;
       char   dopsc;
        if (fin >> dopval >> dopsc) {
    cout << "Ошибка в файле больше данных чем указано размерами таблицы!" << endl;
    return false;
}
        
        fin.close();
        return true;
       } 
  
	  
	 
	  void print()  {
        for ( int i = 0; i < numstrok; i++) {
            for ( int j = 0; j < numstolb; j++) {
                temp[i][j].print();
                cout << " ";
            }
            cout << endl;
        }
    }
    
	};
	

int main ()
{ 

int com=-1;
table t1,t2,t3;
 if (!t1.readFromFile("input1.txt") || !t2.readFromFile("input2.txt")) {
        exit(1);
    }
 int strok;
while(com!=0)
{ cout << "1 - Прочитать и вывести"<<endl
	   << "2 - Средняя температура по строке"<<endl
	   <<"3 - Минимальная температура по строке"<<endl
	   <<"4 - Сумма двух таблиц"<<endl
	   <<"5 - Максимальная температура для таблицы"<<endl
	   <<"0 -  Выход из программы"<<endl;
	   cin>>com;
	switch(com)
	{
		case 1:
		   if (!t1.readFromFile("input1.txt") || !t2.readFromFile("input2.txt")) {
                  exit(1);
               }
                    cout << "\nТаблица 1:\n";
                    t1.print();
                    cout << "\nТаблица 2:\n";
                    t2.print();
		 break;
		 
		 case 2: {
	 cout << "Введите номер строки: ";
    cin >> strok;

    double sr; 
    if (t1.sredn(strok - 1, &sr)) {
        cout << "Средняя температура: " << sr << " C" << endl;
    }
    break;
}  
		 
		 case 3: {
    cout << "Введите номер строки" << endl;
    cin >> strok;
    double minimum;
    if (t1.min_in_strok(strok - 1, &minimum)) {
        cout << "Минимальная температура в " << strok
             << " строке в Цельсиях : " << minimum << endl;
    }
    break;
}
		 
	 
		 case 4:{
		 t3=t1+t2;
		 table summa(t3);
		 cout<<"Результат суммы двух таблиц : "<<endl;
		 t3.print();
		 break;
}
       case 5: {
    double maximum;
    if (t1.maxtable(&maximum)) {
        cout << "Максимальная температура в таблице в Цельсиях  : " << maximum << endl;
    }
    break;
}	 
		 case 0:
		 exit(0);
		default:
		 cout << "Такой команды нет в списке"<<endl;
		 
		}
		
	}

return 0;
}

