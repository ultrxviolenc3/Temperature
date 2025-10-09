#include <iostream>
#include <fstream>
using namespace std;

class temperature{
	
	double temper;
	char scale;
	
	public:
	
	temperature(double t=0.0, char s='C') : temper(t), scale(s) {}
	 void set(double t, char s)  { temper=t; scale=s;
        
    }
	double toC() { 
		
		if( scale == 'C' ) return temper ;
		else if ( scale == 'K' ) return temper - 273.15;
		else if( scale == 'F' ) return (temper - 32.0) / 1.8 ;
		else return -1;
		}
	
       void print()  {
        cout<<"("<<temper<<", "<<scale<<")";
    }
	
	};
	
	class table {
		
		unsigned int numstrok;
		unsigned int numstolb;
		temperature** temp;
		
		public:
		table(unsigned int n = 0, unsigned int k =0) : numstrok(n), numstolb(k)
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
                     return; 
				}
				
			   } 
			} 
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
            cout << "Ошибка: не удалось открыть файл " << filename << endl;
            return false;
        }
        fin >> numstrok >> numstolb;
        if (!fin || numstrok == 0 || numstolb == 0) {
        cout << "Ошибка: неверные размеры таблицы" << endl;
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
    double sredn(unsigned int strok){
		if(strok >= numstrok)
		{
			cout<<"Неверный номер строки"<<endl;
			return 0;
			}
		double sum=0.0;
		for(unsigned int i=0;i<numstolb;i++)
		{ 
			sum+=temp[strok][i].toC();
			}
		return sum / numstolb ;
		}
	
	};
	

int main ()
{ 
int com=-1;
table t1,t2;
 if (!t1.readFromFile("input1.txt") || !t2.readFromFile("input2.txt")) {
        cout << "Ошибка при чтении файлов!" << endl;
    }
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
                    cout << "\nТаблица 1:\n";
                    t1.print();
                    cout << "\nТаблица 2:\n";
                    t2.print();
		 break;
		 
		 case 2:
		 int strok;
		 cout<<"Введите номер строки"<<endl;
		 cin>>strok;
		 cout<<"Средняя температура по "<<strok<<" строке "<<"в Цельсиях : "<< t1.sredn(strok-1)<<endl; 
		 
        break;		 
		 
		/* case 3:
		 break;
		 
		 case 4:
		 break;
*/
         // case 5:
        // break;
		 
		 case 0:
		 exit(1);
		default:
		 cout << "Такой команды нет в списке"<<endl;
		 
		}
		
	}

return 0;
}
 
