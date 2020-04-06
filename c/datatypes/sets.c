#include "sets.h"


static Value lenSet(VM *vm, int argCount, Value *args) {
    if (argCount != 0) {
        runtimeError(vm, "len() takes 0 argument (%d given)", argCount);
        return EMPTY_VAL;
    }

    ObjSet *set = AS_SET(args[0]);
    return NUMBER_VAL(set->count);
}

static Value addSetItem(VM *vm, int argCount, Value *args) {
    if (argCount != 1) {
        runtimeError(vm, "add() takes 1 argument (%d given)", argCount);
        return EMPTY_VAL;
    }


    ObjSet *set = AS_SET(args[0]);
    setInsert(vm, set, args[1]);

    return NIL_VAL;
}

static Value removeSetItem(VM *vm, int argCount, Value *args) {
    if (argCount != 1) {
        runtimeError(vm, "remove() takes 1 argument (%d given)", argCount);
        return EMPTY_VAL;
    }

    ObjSet *set = AS_SET(args[0]);

    if (!setDelete(vm, set, args[1])) {
        runtimeError(vm, "Value '%s' passed to remove() does not exist within the set", AS_CSTRING(args[1]));
        return EMPTY_VAL;
    }

    return NIL_VAL;
}

static Value containsSetItem(VM *vm, int argCount, Value *args) {
    if (argCount != 1) {
        runtimeError(vm, "contains() takes 1 argument (%d given)", argCount);
        return EMPTY_VAL;
    }

    ObjSet *set = AS_SET(args[0]);

    return setGet(set, args[1]) ? TRUE_VAL : FALSE_VAL;
}

void declareSetMethods(VM *vm) {
    defineNative(vm, &vm->setMethods, "len", lenSet);
    defineNative(vm, &vm->setMethods, "add", addSetItem);
    defineNative(vm, &vm->setMethods, "remove", removeSetItem);
    defineNative(vm, &vm->setMethods, "contains", containsSetItem);
}

