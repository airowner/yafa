/*
 * File:   invoke.cpp
 * Author: wuhao
 *
 * Created on 2015年11月30日, 上午1:33
 */

#include "../core.h"

namespace php {
    value call_method(value* obj, const std::string& method, const std::vector<zval>& params) {
        value r;
        zend_fcall_info fci;
        // zend_fcall_info_cache fcc;

        fci.size = sizeof (fci);
        fci.no_separation = 1;
        ZVAL_STRINGL(&fci.function_name, method.c_str(), method.length());
        fci.object = Z_OBJ(obj->val);
        fci.params = const_cast<zval*>(params.data());
        fci.param_count = params.size();
        fci.retval = &r.val;
        #if PHP_VERSION_ID < 70100
          fci.symbol_table = NULL;
          fci.function_table = NULL;
        #endif

    //    fcc.initialized = 1;
    //    fcc.function_handler = (zend_function*)zend_hash_find_ptr(&Z_OBJCE(obj._value)->function_table, Z_STR(fci.function_name));
    //    fcc.calling_scope = Z_OBJCE(obj._value);
    //    fcc.called_scope  = Z_OBJCE(obj._value);
    //    fcc.object = Z_OBJ(obj._value);
        int result = zend_call_function(&fci, nullptr);
        zval_ptr_dtor(&fci.function_name);
        if(result != SUCCESS) {
            zend_throw_error(nullptr, "Couldn't execute method \"%s::%s\"", Z_OBJCE(obj->val)->name->val, method.c_str());
        }
        return r;
    }
    value call_method_0(value* obj, const std::string& method) {
        value r;
        if(obj == nullptr) {
            zend_call_method(nullptr, nullptr, nullptr, method.c_str(), method.length(), &r.val, 0, nullptr, nullptr);
        }else{
            zend_call_method(&obj->val, Z_OBJCE(obj->val), nullptr, method.c_str(), method.length(), &r.val, 0, nullptr, nullptr);
        }
        return std::move(r);
    }

    value call_method_1(value* obj, const std::string& method, const value& a1) {
        value r;
        if(obj == nullptr) {
            zend_call_method(nullptr, nullptr, nullptr, method.c_str(), method.length(), &r.val, 1, const_cast<zval*>(&a1.val), nullptr);
        }else{
            zend_call_method(&obj->val, Z_OBJCE(obj->val), nullptr, method.c_str(), method.length(), &r.val, 1, const_cast<zval*>(&a1.val), nullptr);
        }
        return std::move(r);
    }

    value call_method_2(value* obj, const std::string& method, const value& a1, const value& a2) {
        value r;
        if(obj == nullptr) {
            zend_call_method(nullptr, nullptr, nullptr, method.c_str(), method.length(), &r.val, 2, const_cast<zval*>(&a1.val), const_cast<zval*>(&a2.val));
        }else{
            zend_call_method(&obj->val, Z_OBJCE(obj->val), nullptr, method.c_str(), method.length(), &r.val, 2, const_cast<zval*>(&a1.val), const_cast<zval*>(&a2.val));
        }

        return std::move(r);
    }

//    value create_object(zend_class_entry* ce, const parameter& params) {
//        value obj;
//        object_init_ex(&obj.val, ce);
//        std::vector<zval> param;
//        for(size_t i=0;i<params.size;++i) {
//            param.push_back(params[i].val);
//        }
//        call_method(&obj, "__construct", params);
//    }
}
