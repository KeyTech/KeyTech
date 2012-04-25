#ifndef EXCEPTION_H
#define	EXCEPTION_H

class Exception {
public:
    Exception(char *message);
    
    char *getMessage();

private:
    char *message;
};

#endif	/* EXCEPTION_H */