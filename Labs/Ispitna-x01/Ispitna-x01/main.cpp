MobileServis &operator += (Device &m){
    if(m.getGodina()>2019 || m.getGodina()<2000){
        throw InvalidProductionDate();
    }else{
        Device *temp=new Device[n+1];
        for(int i=0; i<n; i++){
            temp[i]=devices[i];
        }
        
        temp[n++]=m;
        delete [] devices;
        devices=temp;
    }
    
    return *this;
}

Servis &operator += (Device &m){
    Device *temp=new Device[n+1];
    for(int i=0; i<n; i++){
        temp[i]=devices[i];
    }
    
    temp[n++]=m;
    delete [] devices;
    devices=temp;
    
    return *this;
}









Servis &operator += (Device &d){
    Device *temp=new Device[n+1];
    for(int i=0; i<n; i++){
        temp[i]=devices[i];
    }
    
    temp[n++]=m;
    delete [] devices;
    devices=temp;
    
    return *this;
}












Servis &operator += (Device &d){
    Device *temp=new Device[n+1];
    for(int i=0; i<n; i++){
        temp[i]=device[i];
    }
    
    temp[n++]=d;
    delete [] devices;
    devices=temp;
    
    return *this;
}











Servis &operator += (Device &d){
    Device *temp=new Device[n+1];
    for(int i=0; i<n; i++){
        temp[i]=devices[i];
    }
    
    temp[n++]=d;
    delete [] devices;
    devices=temp;
    
    return *this;
}









Servis &operator += (Device &d){
    Device *temp= new Device[n+1];
    for(int i=0; i<n; i++){
        temp[i]=devices[i];
    }
    
    temp[n++]=d;
    delete [] devices;
    devices=temp;
    
    return *this;
}


Servis &operator += (Device &d){
    Device *temp=new Device[n+1];
    for(int i=0; i<n; i++){
        temp[i]=devices[i];
    }
    
    temp[n++]=d;
    delete [] devices;
    devices=temp;
    
    return *this;
}

bool operator > (Device &d){
    if(ured>d.ured)
        return 1;
}else{
    return 0;
}

}


Device &operator += (Device &d){
    Device *temp=new Device[n+1];
    for(int i=0; i<n; i++){
        temp[i]=devices[i];
    }
    
    temp[n++]=d;
    delete [] devices;
    devices=temp;
    
    return *this;
}
