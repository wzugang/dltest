#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>
extern int addvalue;

int sub(int a,int b)
{
    return a - b;
}

int main(int argc, char **argv)
{
    void *handle;
    void *handle2;
    void *handle3;
    double (*cosine)(double);
    char *error;
    int (*add)(int a,int b);
    int (*subf)(int a,int b);
    void (*reg)(void*);

    handle = dlopen("libm.so", RTLD_LAZY);
    handle2 = dlopen("libSDL-1.2.so.0", RTLD_NOW);
    handle3 = dlopen("./test.so", RTLD_NOW);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    if(NULL != handle2)
    {
        printf("sdl local ok.\n");
        dlclose(handle2);
    }
    add = dlsym(handle3,"add");
    reg = dlsym(handle3,"regfunc");
    reg(&sub);
    subf = dlsym(handle3,"testfunc");

    printf("add(2,3)=%d\n",add(2,3));
    printf("subf(5,3)=%d\n",subf(5,3));
    //printf("addvalue=%d\n",addvalue);


    dlerror();    /* Clear any existing error */

    /* Writing: cosine = (double (*)(double)) dlsym(handle, "cos");
       would seem more natural, but the C99 standard leaves
       casting from "void *" to a function pointer undefined.
       The assignment used below is the POSIX.1-2003 (Technical
       Corrigendum 1) workaround; see the Rationale for the
       POSIX specification of dlsym(). */

    *(void **) (&cosine) = dlsym(handle, "cos");

    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    printf("%f\n", (*cosine)(2.0));
    dlclose(handle);
    dlclose(handle3);
    exit(EXIT_SUCCESS);
}

