// abstract class definition for serializing (interface)

#include <iostream>		/// standard input/output library
#include <string>		/// standard input/output library
#include <fstream> // for files manipulation

using namespace std;

class Archive
{
    public:
        Archive() {}
        virtual ~Archive();
        virtual void write(const void* buffer, size_t length) {}
        virtual void read(void* buffer, size_t length) {}
        Archive& operator<<(const string& str);
        Archive& operator>>(string& str);
        Archive& operator<<(int val);
        Archive& operator>>(int& val);
};

class ArchiveFile : public Archive
{
    iostream* _stream;      // reference to the implementation element
    public:
        ArchiveFile(iostream* stream) : _stream(stream) {};
        virtual ~ArchiveFile() {};
        virtual void write(const void *buffer, size_t length);
        virtual void read(void *buffer, size_t length);
};

class Persistant
{
    public:
        virtual ~Persistant() {};
        static Persistant* load(Archive& stream);
        void store(Archive& stream) const;
    protected:
        virtual void serialize(Archive& stream) 
        {}
        virtual int version() const
        {
            return 0;
        }
};

void Persistant::store(Archive& stream)const
{
    string className = typeid(*this).name();
    stream << className;
    //now the class itself (this) takes over the control IoC to implement specific string
    const_cast<Persistant *> (this)->serialize(stream);
};
   
       
class Class2bserial : public Persistant 
{
    int _id;
    void serialize(Archive& stream) 
    {
        stream << _id;          //
    };
        
};

 
int main(int argc, char const *argv[])
{
    fstream file("./data.dat",ios::out | ios::in | ios::binary | ios::trunc );
    // injecting the dependancy
    ArchiveFile stream(&file);

    
    file.seekg(0, ios::beg);
    Class2bserial* newObj = dynamic_cast<Class2bserial*> (Persistant::load(stream));
    
    
        // IoC used by store on the pointer this (inherited from persistent
    newObj->store(stream);
} 
