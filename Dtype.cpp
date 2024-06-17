#include <string>
#include <algorithm>
#include "Dtype.h"

Dtype::Dtype() {

    did = MATH_CPP_DTYPE_INVALID;
    is_resolved = false;
}

Dtype::~Dtype() {

}


/* Concrete class now*/

Dtype_INT::Dtype_INT() {

    this->did = MATH_CPP_INT;
     this->dtype.int_val = 0;
}

Dtype_INT::Dtype_INT(int val) {

    this->did = MATH_CPP_INT;
    this->dtype.int_val = val;
    this->is_resolved = true;
}

Dtype_INT::~Dtype_INT() {

}

MexprNode * 
Dtype_INT::clone() {

    Dtype_INT *obj = new Dtype_INT();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}


void 
Dtype_INT::SetValue(void *value) {

    int val = atoi ((const char *)value);
    this->dtype.int_val = val;
    this->is_resolved = true;
}

void 
Dtype_INT::SetValue(Dtype *value)  {

    this->dtype.int_val = dynamic_cast <Dtype_INT *> (value)->dtype.int_val;
     this->is_resolved = true;
}

mexprcpp_dtypes_t 
Dtype_INT::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    return MATH_CPP_INT;
}

Dtype* 
Dtype_INT::compute(Dtype *dtype1, Dtype *dtype2) {

    return dynamic_cast <Dtype *>(clone() );
}




Dtype_DOUBLE::Dtype_DOUBLE() {

    this->did = MATH_CPP_DOUBLE;
     this->dtype.d_val = 0;
}

Dtype_DOUBLE::Dtype_DOUBLE(double val) {

    this->did = MATH_CPP_DOUBLE;
    this->dtype.d_val = val;
     this->is_resolved = true;
}

Dtype_DOUBLE::~Dtype_DOUBLE() {

}

void 
Dtype_DOUBLE::SetValue(void *value) {

    double val = (double)atof ((const char *)value);
    this->dtype.d_val = val;
     this->is_resolved = true;
}

void 
Dtype_DOUBLE::SetValue(Dtype *value)  {

    this->dtype.d_val = dynamic_cast <Dtype_DOUBLE *> (value)->dtype.d_val;
     this->is_resolved = true;
}

MexprNode * 
Dtype_DOUBLE::clone() {

    Dtype_DOUBLE *obj = new Dtype_DOUBLE();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}

mexprcpp_dtypes_t 
Dtype_DOUBLE::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    return MATH_CPP_DOUBLE;
}

Dtype* 
Dtype_DOUBLE::compute(Dtype *dtype1, Dtype *dtype2) {

    return dynamic_cast <Dtype *>(clone() );
}




Dtype_STRING::Dtype_STRING() {

    this->did = MATH_CPP_STRING;
}

Dtype_STRING::~Dtype_STRING() {

}


void 
Dtype_STRING::SetValue(void *value) {

     this->dtype.str_val.assign(std::string ((char *)value));

     // remove the " " on both the sides of the strings if present.
     // remove the ' ' on both the sides of the string if present.
     // because user enters string in single or double quotes. While stroing the strings, we dont store the doubl/single quotes
    // Chat GPT gave me this to remove " (double quote) or ' (single quote)
    // #include <algorithm> to use below functions
    
         this->dtype.str_val.erase(
            std::remove(this->dtype.str_val.begin(), this->dtype.str_val.end(), '\"'), 
            this->dtype.str_val.end());
        this->dtype.str_val.erase(
            std::remove(this->dtype.str_val.begin(), this->dtype.str_val.end(), '\''), 
            this->dtype.str_val.end());
             this->is_resolved = true;
}

void 
Dtype_STRING::SetValue(Dtype *value)  {

    Dtype_STRING *value_str = dynamic_cast<Dtype_STRING *> (value);
    this->SetValue ((void *)value_str->dtype.str_val.c_str()); // leverage the Ist SetValue fn
     this->is_resolved = true;
}

MexprNode * 
Dtype_STRING::clone() {

    Dtype_STRING *obj = new Dtype_STRING();
    obj->dtype.str_val = this->dtype.str_val;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}

mexprcpp_dtypes_t 
Dtype_STRING::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    return MATH_CPP_STRING;
}

Dtype* 
Dtype_STRING::compute(Dtype *dtype1, Dtype *dtype2) {

    return dynamic_cast <Dtype *>(clone() );
}




Dtype_BOOL::Dtype_BOOL() {

    this->did = MATH_CPP_BOOL;
    this->dtype.b_val = false;
     this->is_resolved = true;
}

Dtype_BOOL::~Dtype_BOOL() {

}

void 
Dtype_BOOL::SetValue(void *value)  {

    // empty
}


void 
Dtype_BOOL::SetValue(Dtype *dtype)  {

    Dtype_BOOL *dtype_bool = dynamic_cast <Dtype_BOOL *> (dtype);
    this->dtype.b_val = dtype_bool->dtype.b_val;
     this->is_resolved = true;
}

MexprNode * 
Dtype_BOOL::clone() {

    Dtype_BOOL *obj = new Dtype_BOOL();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}

mexprcpp_dtypes_t 
Dtype_BOOL::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    return MATH_CPP_BOOL;
}

Dtype* 
Dtype_BOOL::compute(Dtype *dtype1, Dtype *dtype2) {

    return dynamic_cast <Dtype *>(clone() );
}



Dtype_VARIABLE::Dtype_VARIABLE() {

    this->did = MATH_CPP_VARIABLE;
    this->dtype.variable_name.assign("");
    this->is_resolved = false;
    this->resolved_did = MATH_CPP_DTYPE_WILDCRAD;
}

Dtype_VARIABLE::Dtype_VARIABLE(std::string var_name) {

    did = MATH_CPP_VARIABLE;
    this->dtype.variable_name.assign(var_name);
    this->is_resolved = false;
    this->resolved_did = MATH_CPP_DTYPE_WILDCRAD;
}

Dtype_VARIABLE::~Dtype_VARIABLE() {

}

void
Dtype_VARIABLE::SetValue(void *value) {

}

void
Dtype_VARIABLE::SetValue(Dtype *dtype) {

}

MexprNode * 
Dtype_VARIABLE::clone() {

    Dtype_VARIABLE *obj = new Dtype_VARIABLE(this->dtype.variable_name);
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}

mexprcpp_dtypes_t 
Dtype_VARIABLE::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    if (this->is_resolved) return this->resolved_did;
    return MATH_CPP_DTYPE_WILDCRAD;
}

Dtype *
Dtype_VARIABLE::compute(Dtype *dtype1, Dtype *dtype2) {

    if (!this->is_resolved) return NULL;
    Dtype *res = this->compute_fn_ptr ((char *)this->dtype.variable_name.c_str(), this->data_src);
    return res;
}

void  
Dtype_VARIABLE::ResolveOperand (
                mexprcpp_dtypes_t resolved_did,
                void *data_src,
                Dtype *(*compute_fn_ptr)(char *, void *))  {

    assert (!this->is_resolved);

    this->data_src = data_src;

    this->compute_fn_ptr = compute_fn_ptr;

    this->is_resolved = true;

    this->resolved_did = resolved_did;
}



 Dtype * 
 Dtype::factory(mexprcpp_dtypes_t did) {

    switch (did) {

        case MATH_CPP_INT:
            return new Dtype_INT();
        case MATH_CPP_DOUBLE:
            return new Dtype_DOUBLE();
        case MATH_CPP_STRING:
            return new Dtype_STRING();
        case MATH_CPP_BOOL:
            return new Dtype_BOOL();
        case MATH_CPP_VARIABLE:
            return new Dtype_VARIABLE();
        default:
            return NULL;
    }
 }