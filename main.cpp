#include <iostream>

using namespace std;

class Vector
{
private:
    int *a;
    int nr;
public:
    Vector();
    Vector (int *, int);
    Vector (const Vector&);
    ~Vector();
    friend istream& operator>> (istream&, Vector&);
    friend ostream& operator<< (ostream&, const Vector&);
    void afisare (ostream& out) const
    {
        out << endl << "Numar: ";
        int i;
        for (i = nr; i >= 1; i--)
            out << a[i];
        out << endl;
    }
    Vector& operator= (const Vector&);
    int* get_a() const;
    int get_nr() const;
    int nr_pe_poz (int) const;
    void set_nr_poz (int, int);
    void alocare_a (int);
    void set_nr (int n);
    void add_Vector (int, int*);
    int operator== (const Vector&) const;
    int operator> (const Vector&) const;
};

int Vector::operator== (const Vector &N) const
{
    if (nr != N.nr)
        return 0;
    int i;
    for (i = 1; i <= nr; i++)
        if (a[i] != N.a[i])
            return 0;
    return 1;
}

int Vector::operator> (const Vector &N) const
{
    if (nr > N.nr)
        return 1;
    else if (nr < N.nr)
        return 0;
    int i;
    for (i = nr; i >= 1; i--)
        if (a[i] > N.a[i])
            return 1;
        else
            return 0;
    return 0;
}

void Vector::add_Vector (int n, int *b)
{
    nr = n;
    a = b;
}

void Vector::set_nr (int n)
{
    nr = n;
}

void Vector::alocare_a (int nr)
{
    delete []a;
    a = new int[nr + 2];
}

void Vector::set_nr_poz (int poz, int nr)
{
    this->a[poz] = nr;
}

int Vector::nr_pe_poz (int poz) const
{
    return this->a[poz];
}

Vector::Vector()
{
    //cout << "Constructor vector" << endl;
    nr = 0;
    a = NULL;
}

Vector::Vector (int* b, int nrb)
{
    //cout << "Constructor parametrizat " << endl ;
    a = new int[nrb + 2];
    nr = nrb;
    int i;
    for (i = 1; i <= nr; i++)
    {
        a[i] = b[i];
    }
}

Vector::Vector (const Vector &V)
{
    //cout << "Constructor de copiere vector" << endl;
    *this = V;
}

Vector::~Vector()
{
    //cout << "Destructor vector" << endl;
    if (nr != 0)
        delete []a;
    nr = 0;
}

Vector& Vector::operator= (const Vector& N)
{
    if (this == &N)
        return *this;
    if (nr != 0)
        delete []a;
    a = new int[N.nr + 2];
    int i;
    nr = N.nr;
    for (i = 1; i <= nr; i++)
        a[i] = N.a[i];
    return *this;
}

istream& operator>> (istream& in, Vector &V)
{
    if (V.nr != 0)
        delete []V.a;
    cout << "Numar de elemente:";
    in >> V.nr;
    cout << "Elem. vector:";
    int data;
    V.a = new int[V.nr + 2];
    for (int i = 1; i <= V.nr; i++)
    {
        in >> data;
        V.a[i] = data;
    }
    return in;
}

ostream& operator<< (ostream &out, const Vector &V)
{
    V.afisare (out);
    return out;
}

int* Vector::get_a() const
{
    return a;
}

int Vector::get_nr()  const
{
    return nr;
}

class Nr_natural_mare
{
protected:
    int nr_cifre;
    Vector V;
public:
    Nr_natural_mare();
    Nr_natural_mare (int, Vector V);
    Nr_natural_mare (const Nr_natural_mare&);
    ~Nr_natural_mare();
    Nr_natural_mare& operator= (const Nr_natural_mare&);
    friend istream& operator>> (istream&, Nr_natural_mare&);
    friend ostream& operator<< (ostream&, const Nr_natural_mare&);
    virtual void afisare (ostream& out) const
    {
        this->V.Vector::afisare (out);
    }
    void set_nr_cif (int);
    int get_nr_cifre() const;
    int cifra (int poz) const;
    void add_Nr_nat (int*, int);
    Nr_natural_mare operator+ (const Nr_natural_mare&);
    int operator== (const Nr_natural_mare&) const;
    int operator> (const Nr_natural_mare&) const;
    const Vector* adresa_V() const;
};

const Vector* Nr_natural_mare::adresa_V()  const
{
    return &(this->V);
}

int Nr_natural_mare::operator== (const Nr_natural_mare &NR) const
{
    if (nr_cifre != NR.nr_cifre)
        return 0;
    if (V == NR.V)
        return 1;
    return 0;
}

int Nr_natural_mare::operator> (const Nr_natural_mare &NR) const
{
    if (nr_cifre > NR.nr_cifre)
        return 1;
    else if (nr_cifre < NR.nr_cifre)
        return 0;
    if (V > NR.V)
        return 1;
    return 0;
}

void Nr_natural_mare::add_Nr_nat (int *v, int nv)
{
    nr_cifre = nv;
    V.add_Vector (nv, v);
}

Nr_natural_mare Nr_natural_mare::operator+ (const Nr_natural_mare &Nr)
{
    Nr_natural_mare rez;
    if (Nr.nr_cifre > nr_cifre)
    {
        rez.nr_cifre = Nr.nr_cifre;
        int i;
        int ad = 0;
        rez.V.alocare_a (Nr.nr_cifre);
        for (i = 1; i <= nr_cifre; i++)
        {
            int c = Nr.V.nr_pe_poz (i) + V.nr_pe_poz (i) + ad;
            ad = c / 10;
            rez.V.set_nr_poz (i, c % 10);
        }
        for (; i <= Nr.nr_cifre; i++)
        {
            int c = Nr.V.nr_pe_poz (i) + ad;
            ad = c / 10;
            rez.V.set_nr_poz (i, c % 10);
        }
        if (ad != 0)
        {
            rez.nr_cifre++;
            rez.V.set_nr_poz (rez.nr_cifre, ad);
        }
    }
    else
    {
        rez.nr_cifre = nr_cifre;
        int i;
        int ad = 0;
        rez.V.alocare_a (nr_cifre);
        for (i = 1; i <= Nr.nr_cifre; i++)
        {
            int c = Nr.V.nr_pe_poz (i) + V.nr_pe_poz (i) + ad;
            ad = c / 10;
            rez.V.set_nr_poz (i, c % 10);
        }
        for (; i <= nr_cifre; i++)
        {
            int c = V.nr_pe_poz (i) + ad;
            ad = c / 10;
            rez.V.set_nr_poz (i, c % 10);
        }
        if (ad != 0)
        {
            rez.nr_cifre++;
            rez.V.set_nr_poz (rez.nr_cifre, ad);
        }
    }
    rez.V.set_nr (rez.nr_cifre);
    return rez;
}

int Nr_natural_mare::cifra (int poz) const
{
    //ver
    return V.nr_pe_poz (poz);
}

int Nr_natural_mare::get_nr_cifre()  const
{
    return nr_cifre;
}

void Nr_natural_mare::set_nr_cif (int n)
{
    nr_cifre = n;
}

Nr_natural_mare::Nr_natural_mare()
{
    //cout << "Constructor nr_mare" << endl;
    nr_cifre = 0;
}

Nr_natural_mare::Nr_natural_mare (int nr_cif, Vector VN)
{
    //cout << "Constructor parametrizat nr_mar" << endl;
    nr_cifre = nr_cif;
    V=VN;
}

Nr_natural_mare::Nr_natural_mare (const Nr_natural_mare& N)
{
    //cout << "Constructor de copiere nr_mare" << endl;
    nr_cifre = N.nr_cifre;
    V=N.V;
}

Nr_natural_mare& Nr_natural_mare::operator= (const Nr_natural_mare& N)
{
    if (this == &N)
        return *this;
    nr_cifre = N.nr_cifre;
    this->V = N.V;
    return *this;
}

Nr_natural_mare:: ~Nr_natural_mare()
{
    //cout << "Destructor nr_mare" << endl;
    nr_cifre = 0;
}

istream& operator>> (istream& in, Nr_natural_mare& N)
{
    in >> N.V;
    N.set_nr_cif (N.V.get_nr());
    return in;
}

ostream& operator<< (ostream& out, const Nr_natural_mare& N)
{
    N.afisare (out);
    return out;
}

class Nr_Fibonacii_mare: public Nr_natural_mare
{
public:
    Nr_Fibonacii_mare();
    Nr_Fibonacii_mare (const Nr_natural_mare&);
    Nr_Fibonacii_mare (const Nr_Fibonacii_mare&);
    ~Nr_Fibonacii_mare() ;
    friend istream& operator>> (istream&, Nr_Fibonacii_mare&);
    friend ostream& operator<< (ostream&, const Nr_Fibonacii_mare&);
    void afisare (ostream& out) const
    {
        this->Nr_natural_mare::afisare (out);
    }
    Nr_Fibonacii_mare& operator= (const Nr_Fibonacii_mare&);
    Nr_Fibonacii_mare operator+ (const Nr_Fibonacii_mare&);
    friend void descompunere_Nr_Fibo (ostream&, Nr_Fibonacii_mare*, const Nr_Fibonacii_mare&);
    void add_Nr_Fibo (int, int*);
    int operator!= (const Nr_Fibonacii_mare&) const;
    int operator== (const Nr_Fibonacii_mare&) const;
    int operator> (const Nr_Fibonacii_mare&)const;
};

int Nr_Fibonacii_mare::operator!= (const Nr_Fibonacii_mare& NR) const
{
    if(Nr_natural_mare::operator==(NR))
        return 0;
    return 1;
}

int Nr_Fibonacii_mare::operator== (const Nr_Fibonacii_mare& NR) const
{
    if(Nr_natural_mare::operator==(NR))
        return 1;
    return 0;
}

int Nr_Fibonacii_mare::operator> (const Nr_Fibonacii_mare& NR) const
{
    if (Nr_natural_mare::operator>(NR))
        return 1;
    return 0;
}

void Nr_Fibonacii_mare::add_Nr_Fibo (int n, int *b)
{
    add_Nr_nat (b, n);
}

Nr_Fibonacii_mare::Nr_Fibonacii_mare(): Nr_natural_mare()
{
    //cout << "Constructor Nr_fibo" << endl;
}

Nr_Fibonacii_mare::Nr_Fibonacii_mare(const Nr_natural_mare &N): Nr_natural_mare(N)
{
    //cout << "Constructor cu nr mare" << endl;
}

Nr_Fibonacii_mare::~Nr_Fibonacii_mare()
{
    //cout << "Destructor Nr_fibo" << endl;
}

istream& operator>> (istream& in, Nr_Fibonacii_mare &NR)
{
    in>>(Nr_natural_mare&)NR;
    return in;
}

ostream& operator<< (ostream& out, const Nr_Fibonacii_mare &NR)
{
    NR.afisare (out);
    return out;
}

Nr_Fibonacii_mare& Nr_Fibonacii_mare::operator= (const Nr_Fibonacii_mare& NR)
{
    Nr_natural_mare::operator=(NR);
    return *this;
}

void descompunere_Nr_Fibo (ostream& out, Nr_Fibonacii_mare *F, const Nr_Fibonacii_mare &NR)
{
    int *b = new int[2];
    int *c = new int[2];
    b[1] = 1;
    c[1] = 1;
    F[1].add_Nr_Fibo (1, b);
    F[2].add_Nr_Fibo (1, c);
    if (F[2] == NR)
    {
        out << "Descompunerea:" << endl;
        out << F[1];
        out << F[2];
        out << "lui:" << endl;
        out << NR;
        return;
    }
    Nr_Fibonacii_mare REZ;
    REZ = F[1] + (F[2]);
    F[3] = REZ;
    int n = 3;
    int ok = 1;
    while (REZ != NR)
    {
        if (REZ > NR)
        {
            ok = 0;
            break;
        }
        REZ = F[n - 1] + F[n];
        n++;
        F[n] = REZ;
    }
    if (ok == 0)
        out << NR << " nu e numar Fibonacci" << endl;
    else
    {
        out << "Descompunerea:" << endl;
        out << F[n - 2];
        out << F[n - 1];
        out << "lui:" << endl;
        out << NR;
    }
}

Nr_Fibonacii_mare Nr_Fibonacii_mare::operator+ (const Nr_Fibonacii_mare &NR)
{
    Nr_Fibonacii_mare REZ;
    REZ=*this;
    Nr_Fibonacii_mare F(REZ.Nr_natural_mare::operator+(NR));
    return F;
}

int main()
{
    ///Introduc cifrele invers
    Nr_Fibonacii_mare *F = new Nr_Fibonacii_mare[1000];
    Nr_Fibonacii_mare *M = new Nr_Fibonacii_mare;
    cin >> *M;
    descompunere_Nr_Fibo (cout, F, *M);
    delete []F;
    delete M;

    ///Citirea informatiilor a n elemente si afisarea lor;
    /*Nr_Fibonacii_mare *N=new Nr_Fibonacii_mare[50];
    int n;
    cout<<endl<<endl<<"n= ";
    cin>>n;
    cout<<endl;
    int i;
    for(i=1;i<=n;i++)
    {
        cin>>N[i];
    }
    cout<<endl;
    for(i=1;i<=n;i++)
    {
        cout<<N[i];
    }
    delete []N;
    */
    return 0;
}
