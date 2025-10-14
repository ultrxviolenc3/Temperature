#include <iostream>
#include <fstream>
#include <stdexcept>
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
		else return (temper - 32.0) / 1.8 ; //F
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
		
		unsigned int numstrok;
		unsigned int numstolb;
		temperature** temp;
		
		public:
		table(unsigned int n = 0, unsigned int k =0) : numstrok(n), numstolb(k), temp(nullptr)
		{
			if(n > 0 && k > 0) {
			
				temp=new (nothrow) temperature*[n];
				if(!temp)
				{
					cout<<"Ошибка выделения памяти"<<endl;
					return;
					}
				for(unsigned int i=0; i<n; i++)
			{
			  temp[i] = new (nothrow) temperature[k];
				  if (!temp[i]) {
                cout << "Ошибка выделение памяти"<< endl;
                for (unsigned int j = 0; j < i; ++j) {
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
		{ cout << "Konstruktor kop\n"; 
    numstrok = other.numstrok;
    numstolb = other.numstolb;

    if (numstrok > 0 && numstolb > 0) {
        temp = new temperature*[numstrok];
        for (unsigned int i = 0; i < numstrok; i++) {
            temp[i] = new temperature[numstolb];
            for (unsigned int j = 0; j < numstolb; j++) {
                temp[i][j] = other.temp[i][j]; 
            }
        }
    } else {
        temp = nullptr;
            }
       }
		double sredn(unsigned int strok){ ///sredn
		if(strok >= numstrok)
		{
			 throw std::out_of_range ("Неверный номер строки");
			}
		double sum=0.0;
		for(unsigned int i=0;i<numstolb;i++)
		{ 
			sum+=temp[strok][i].toC();
			}
		return sum / numstolb ;
		}
		
		 double min_in_strok(unsigned int strok) { ///min
    if (strok >= numstrok) {
        throw std::out_of_range("Неверный номер строки" );
        
    }
    double min_val = temp[strok][0].toC();
    for (unsigned int i = 1; i < numstolb; ++i) {
        double val = temp[strok][i].toC();
        if (val < min_val)
            min_val = val;
    }

    return min_val;
  }
  
  double maxtable() { ///max
    

    double max_val = temp[0][0].toC();

    for (unsigned int i = 0; i < numstrok; ++i) {
        for (unsigned int j = 0; j < numstolb; ++j) {
            double val = temp[i][j].toC();
            if (val > max_val)
                max_val = val;
        }
    }
    return max_val;
}
table operator+(const table& other) { ///peregruzka
    if (numstrok != other.numstrok || numstolb != other.numstolb) {
        cout << "Ошибка: таблицы разных размеров, сложение невозможно!" << endl;
        return false;
    }

    table result(numstrok, numstolb);

    for (unsigned int i = 0; i < numstrok; i++) {
        for (unsigned int j = 0; j < numstolb; j++) {
            double t1 = temp[i][j].toC();               
            double t2 = other.temp[i][j].toC();        
            double sumC = t1 + t2;                     

            char scale = temp[i][j].getscale();   
            double summa;

            if (scale == 'C') summa = sumC;
            else if (scale == 'K') summa = sumC + 273.15;
            else summa = sumC * 1.8 + 32.0;         

            result.temp[i][j].set(summa, scale);
        }
    }
    return result;
}
  
		~table() {
			
			if(temp)
			{
				for(unsigned int i = 0;i<numstrok;i++)
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
        fin >> numstrok >> numstolb;
        if (!fin || numstrok == 0 || numstolb == 0) {
        cout << "Ошибка неверные размеры таблицы" << endl;
        return false;
    }
    if (temp) {
    for (unsigned int i = 0; i < numstrok; ++i)
        delete[] temp[i];
    delete[] temp;
    temp = nullptr;
}
        temp = new (nothrow) temperature*[numstrok];
          if (!temp) {
        cout << "Ошибка выделения памяти" << endl;
        return false;
    }
        for (unsigned int i = 0; i < numstrok; i++){
            temp[i] = new (nothrow) temperature[numstolb];
         if (!temp[i]) {
           cout << "Ошибка выделения памяти " << endl;
            temp = nullptr;
        return false;
    
    }
   } 
    

        for (unsigned int i = 0; i < numstrok; ++i) {
            for (unsigned int j = 0; j < numstolb; ++j) {
                double val;
                char sc;
                fin >> val >> sc;
                temp[i][j].set(val, sc);
            }
        } 
        fin.close();
        return true;
       } 
  
	  
	 
	  void print()  {
        for (unsigned int i = 0; i < numstrok; ++i) {
            for (unsigned int j = 0; j < numstolb; ++j) {
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
		 
		 case 2:
		{
		 cout<<"Введите номер строки"<<endl;
		 cin>>strok;
		 try {
			 double sredn=t1.sredn(strok-1);
		 cout<<"Средняя температура по "<<strok<<" строке "<<"в Цельсиях : "<< sredn <<endl; 
	}
	catch (const std::out_of_range& e) {
        cout << e.what() << endl; 
    }
        break;		 
      }  
		 
		 case 3: {
		 cout << "Введите номер строки"<<endl;
         cin >> strok;
         try {
			 double min=t1.sredn(strok-1);
        cout << "Минимальная температура в " << strok << " строке "<< "в Цельсиях : " <<min<< endl; 
        }
        catch (const std::out_of_range& e){
			
			cout << e.what() << endl;
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
        case 5:
        cout<<"Максимальная температура в таблице в Цельсиях  : " << t1.maxtable() << endl; 
        break;		 
		 case 0:
		 exit(0);
		default:
		 cout << "Такой команды нет в списке"<<endl;
		 
		}
		
	}

return 0;
}
///Остались :  проверки
///  проверить на примере  
