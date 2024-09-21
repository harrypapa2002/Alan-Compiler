
%reverse_closure = type { ptr, ptr }
%innerIncrement_closure = type { ptr, ptr, ptr, ptr }
%foo_closure = type { ptr, ptr, ptr, ptr }

@global_str = private unnamed_addr constant [12 x i8] c"u in foo = \00", align 1
@global_str.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.3 = private unnamed_addr constant [15 x i8] c"v[5] in foo = \00", align 1
@global_str.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.5 = private unnamed_addr constant [12 x i8] c"r in foo = \00", align 1
@global_str.6 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.7 = private unnamed_addr constant [17 x i8] c"arr[5] in foo = \00", align 1
@global_str.8 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.9 = private unnamed_addr constant [23 x i8] c"u in innerIncrement = \00", align 1
@global_str.10 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.11 = private unnamed_addr constant [26 x i8] c"v[5] in innerIncrement = \00", align 1
@global_str.12 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.13 = private unnamed_addr constant [23 x i8] c"r in innerIncrement = \00", align 1
@global_str.14 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.15 = private unnamed_addr constant [28 x i8] c"arr[5] in innerIncrement = \00", align 1
@global_str.16 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.17 = private unnamed_addr constant [16 x i8] c"u in reverse = \00", align 1
@global_str.18 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.19 = private unnamed_addr constant [19 x i8] c"v[5] in reverse = \00", align 1
@global_str.20 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.21 = private unnamed_addr constant [16 x i8] c"r in reverse = \00", align 1
@global_str.22 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.23 = private unnamed_addr constant [21 x i8] c"arr[5] in reverse = \00", align 1
@global_str.24 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.25 = private unnamed_addr constant [13 x i8] c"y in main = \00", align 1
@global_str.26 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.27 = private unnamed_addr constant [16 x i8] c"z[5] in main = \00", align 1
@global_str.28 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.29 = private unnamed_addr constant [13 x i8] c"r in main = \00", align 1
@global_str.30 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.31 = private unnamed_addr constant [18 x i8] c"arr[5] in main = \00", align 1
@global_str.32 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.33 = private unnamed_addr constant [18 x i8] c"arr[5] in main = \00", align 1
@global_str.34 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

declare void @writeInteger(i32)

declare void @writeByte(i8)

declare void @writeChar(i8)

declare void @writeString(ptr)

declare i32 @readInteger()

declare i8 @readByte()

declare i8 @readChar()

declare void @readString(i32, ptr)

declare i32 @extend(i8)

declare i8 @shrink(i32)

declare i32 @strlen(ptr)

declare i32 @strcmp(ptr, ptr)

declare void @strcpy(ptr, ptr)

declare void @strcat(ptr, ptr)

define i32 @main() {
entry:
  call void @main.1()
  ret i32 0
}

define void @main.1() {
main_entry:
  %y = alloca i32, align 4
  store i32 0, ptr %y, align 4
  %z = alloca [10 x i32], align 4
  store [10 x i32] zeroinitializer, ptr %z, align 4
  %r = alloca i32, align 4
  store i32 0, ptr %r, align 4
  %arr = alloca [10 x i8], align 1
  store [10 x i8] zeroinitializer, ptr %arr, align 1
  store i32 5, ptr %r, align 4
  %reverse_closure_instance = alloca %reverse_closure, align 8
  %arr_ptr = getelementptr inbounds %reverse_closure, ptr %reverse_closure_instance, i32 0, i32 0
  store ptr %arr, ptr %arr_ptr, align 8
  %r_ptr = getelementptr inbounds %reverse_closure, ptr %reverse_closure_instance, i32 0, i32 1
  store ptr %r, ptr %r_ptr, align 8
  %reverse_arg = load i32, ptr %y, align 4
  call void @reverse(ptr %reverse_closure_instance, i32 %reverse_arg, ptr %z)
  call void @writeString(ptr @global_str.25)
  %writeInteger_arg = load i32, ptr %y, align 4
  call void @writeInteger(i32 %writeInteger_arg)
  call void @writeString(ptr @global_str.26)
  call void @writeString(ptr @global_str.27)
  %elementptr = getelementptr [10 x i32], ptr %z, i32 0, i32 5
  %writeInteger_arg1 = load i32, ptr %elementptr, align 4
  call void @writeInteger(i32 %writeInteger_arg1)
  call void @writeString(ptr @global_str.28)
  %left_load = load i32, ptr %r, align 4
  %addtmp = add i32 %left_load, 1
  store i32 %addtmp, ptr %r, align 4
  call void @writeString(ptr @global_str.29)
  %writeInteger_arg2 = load i32, ptr %r, align 4
  call void @writeInteger(i32 %writeInteger_arg2)
  call void @writeString(ptr @global_str.30)
  %elementptr3 = getelementptr [10 x i8], ptr %arr, i32 0, i32 5
  %left_load4 = load i8, ptr %elementptr3, align 1
  %eqtmp = icmp eq i8 %left_load4, 99
  %0 = zext i1 %eqtmp to i32
  %if_cond = icmp ne i32 %0, 0
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %main_entry
  call void @writeString(ptr @global_str.31)
  %elementptr5 = getelementptr [10 x i8], ptr %arr, i32 0, i32 5
  %writeChar_arg = load i8, ptr %elementptr5, align 1
  call void @writeChar(i8 %writeChar_arg)
  call void @writeString(ptr @global_str.32)
  %elementptr6 = getelementptr [10 x i8], ptr %arr, i32 0, i32 5
  store i8 100, ptr %elementptr6, align 1
  br label %ifcont

else:                                             ; preds = %main_entry
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  call void @writeString(ptr @global_str.33)
  %elementptr7 = getelementptr [10 x i8], ptr %arr, i32 0, i32 5
  %writeChar_arg8 = load i8, ptr %elementptr7, align 1
  call void @writeChar(i8 %writeChar_arg8)
  call void @writeString(ptr @global_str.34)
  ret void
}

define void @reverse(ptr %closure, i32 %u, ptr %v) {
reverse_entry:
  %arr_ptr = getelementptr inbounds %reverse_closure, ptr %closure, i32 0, i32 0
  %arr = load ptr, ptr %arr_ptr, align 8
  %arr1 = alloca ptr, align 8
  store ptr %arr, ptr %arr1, align 8
  %r_ptr = getelementptr inbounds %reverse_closure, ptr %closure, i32 0, i32 1
  %r = load ptr, ptr %r_ptr, align 8
  %r2 = alloca ptr, align 8
  store ptr %r, ptr %r2, align 8
  %u3 = alloca i32, align 4
  store i32 %u, ptr %u3, align 4
  %v4 = alloca ptr, align 8
  store ptr %v, ptr %v4, align 8
  %innerIncrement_closure_instance = alloca %innerIncrement_closure, align 8
  %arr_ptr5 = getelementptr inbounds %innerIncrement_closure, ptr %innerIncrement_closure_instance, i32 0, i32 0
  %arr_load = load ptr, ptr %arr1, align 8
  store ptr %arr_load, ptr %arr_ptr5, align 8
  %v_ptr = getelementptr inbounds %innerIncrement_closure, ptr %innerIncrement_closure_instance, i32 0, i32 1
  %v_load = load ptr, ptr %v4, align 8
  store ptr %v_load, ptr %v_ptr, align 8
  %u_ptr = getelementptr inbounds %innerIncrement_closure, ptr %innerIncrement_closure_instance, i32 0, i32 2
  store ptr %u3, ptr %u_ptr, align 8
  %r_ptr6 = getelementptr inbounds %innerIncrement_closure, ptr %innerIncrement_closure_instance, i32 0, i32 3
  %r_load = load ptr, ptr %r2, align 8
  store ptr %r_load, ptr %r_ptr6, align 8
  call void @innerIncrement(ptr %innerIncrement_closure_instance)
  %left_load = load i32, ptr %u3, align 4
  %addtmp = add i32 %left_load, 10
  store i32 %addtmp, ptr %u3, align 4
  %r_load7 = load ptr, ptr %r2, align 8
  %left_load8 = load i32, ptr %r_load7, align 4
  %addtmp9 = add i32 %left_load8, 9
  %r_load10 = load ptr, ptr %r2, align 8
  store i32 %addtmp9, ptr %r_load10, align 4
  call void @writeString(ptr @global_str.17)
  %writeInteger_arg = load i32, ptr %u3, align 4
  call void @writeInteger(i32 %writeInteger_arg)
  call void @writeString(ptr @global_str.18)
  %v_arrayptr = load ptr, ptr %v4, align 8
  %elementptr = getelementptr i32, ptr %v_arrayptr, i32 5
  %left_load11 = load i32, ptr %elementptr, align 4
  %addtmp12 = add i32 %left_load11, 10
  %v_arrayptr13 = load ptr, ptr %v4, align 8
  %elementptr14 = getelementptr i32, ptr %v_arrayptr13, i32 5
  store i32 %addtmp12, ptr %elementptr14, align 4
  call void @writeString(ptr @global_str.19)
  %v_arrayptr15 = load ptr, ptr %v4, align 8
  %elementptr16 = getelementptr i32, ptr %v_arrayptr15, i32 5
  %writeInteger_arg17 = load i32, ptr %elementptr16, align 4
  call void @writeInteger(i32 %writeInteger_arg17)
  call void @writeString(ptr @global_str.20)
  call void @writeString(ptr @global_str.21)
  %r_load18 = load ptr, ptr %r2, align 8
  %writeInteger_arg19 = load i32, ptr %r_load18, align 4
  call void @writeInteger(i32 %writeInteger_arg19)
  call void @writeString(ptr @global_str.22)
  %arr_arrayptr = load ptr, ptr %arr1, align 8
  %elementptr20 = getelementptr i8, ptr %arr_arrayptr, i32 5
  %left_load21 = load i8, ptr %elementptr20, align 1
  %eqtmp = icmp eq i8 %left_load21, 98
  %0 = zext i1 %eqtmp to i32
  %if_cond = icmp ne i32 %0, 0
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %reverse_entry
  call void @writeString(ptr @global_str.23)
  %arr_arrayptr22 = load ptr, ptr %arr1, align 8
  %elementptr23 = getelementptr i8, ptr %arr_arrayptr22, i32 5
  %writeChar_arg = load i8, ptr %elementptr23, align 1
  call void @writeChar(i8 %writeChar_arg)
  call void @writeString(ptr @global_str.24)
  %arr_arrayptr24 = load ptr, ptr %arr1, align 8
  %elementptr25 = getelementptr i8, ptr %arr_arrayptr24, i32 5
  store i8 99, ptr %elementptr25, align 1
  br label %ifcont

else:                                             ; preds = %reverse_entry
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  ret void
}

define void @innerIncrement(ptr %closure) {
innerIncrement_entry:
  %arr_ptr = getelementptr inbounds %innerIncrement_closure, ptr %closure, i32 0, i32 0
  %arr = load ptr, ptr %arr_ptr, align 8
  %arr1 = alloca ptr, align 8
  store ptr %arr, ptr %arr1, align 8
  %v_ptr = getelementptr inbounds %innerIncrement_closure, ptr %closure, i32 0, i32 1
  %v = load ptr, ptr %v_ptr, align 8
  %v2 = alloca ptr, align 8
  store ptr %v, ptr %v2, align 8
  %u_ptr = getelementptr inbounds %innerIncrement_closure, ptr %closure, i32 0, i32 2
  %u = load ptr, ptr %u_ptr, align 8
  %u3 = alloca ptr, align 8
  store ptr %u, ptr %u3, align 8
  %r_ptr = getelementptr inbounds %innerIncrement_closure, ptr %closure, i32 0, i32 3
  %r = load ptr, ptr %r_ptr, align 8
  %r4 = alloca ptr, align 8
  store ptr %r, ptr %r4, align 8
  %foo_closure_instance = alloca %foo_closure, align 8
  %arr_ptr5 = getelementptr inbounds %foo_closure, ptr %foo_closure_instance, i32 0, i32 0
  %arr_load = load ptr, ptr %arr1, align 8
  store ptr %arr_load, ptr %arr_ptr5, align 8
  %v_ptr6 = getelementptr inbounds %foo_closure, ptr %foo_closure_instance, i32 0, i32 1
  %v_load = load ptr, ptr %v2, align 8
  store ptr %v_load, ptr %v_ptr6, align 8
  %u_ptr7 = getelementptr inbounds %foo_closure, ptr %foo_closure_instance, i32 0, i32 2
  %u_load = load ptr, ptr %u3, align 8
  store ptr %u_load, ptr %u_ptr7, align 8
  %r_ptr8 = getelementptr inbounds %foo_closure, ptr %foo_closure_instance, i32 0, i32 3
  %r_load = load ptr, ptr %r4, align 8
  store ptr %r_load, ptr %r_ptr8, align 8
  call void @foo(ptr %foo_closure_instance)
  %u_load9 = load ptr, ptr %u3, align 8
  %left_load = load i32, ptr %u_load9, align 4
  %addtmp = add i32 %left_load, 3
  %u_load10 = load ptr, ptr %u3, align 8
  store i32 %addtmp, ptr %u_load10, align 4
  %r_load11 = load ptr, ptr %r4, align 8
  %left_load12 = load i32, ptr %r_load11, align 4
  %addtmp13 = add i32 %left_load12, 20
  %r_load14 = load ptr, ptr %r4, align 8
  store i32 %addtmp13, ptr %r_load14, align 4
  call void @writeString(ptr @global_str.9)
  %u_load15 = load ptr, ptr %u3, align 8
  %writeInteger_arg = load i32, ptr %u_load15, align 4
  call void @writeInteger(i32 %writeInteger_arg)
  call void @writeString(ptr @global_str.10)
  %v_arrayptr = load ptr, ptr %v2, align 8
  %elementptr = getelementptr i32, ptr %v_arrayptr, i32 5
  %left_load16 = load i32, ptr %elementptr, align 4
  %addtmp17 = add i32 %left_load16, 3
  %v_arrayptr18 = load ptr, ptr %v2, align 8
  %elementptr19 = getelementptr i32, ptr %v_arrayptr18, i32 5
  store i32 %addtmp17, ptr %elementptr19, align 4
  call void @writeString(ptr @global_str.11)
  %v_arrayptr20 = load ptr, ptr %v2, align 8
  %elementptr21 = getelementptr i32, ptr %v_arrayptr20, i32 5
  %writeInteger_arg22 = load i32, ptr %elementptr21, align 4
  call void @writeInteger(i32 %writeInteger_arg22)
  call void @writeString(ptr @global_str.12)
  call void @writeString(ptr @global_str.13)
  %r_load23 = load ptr, ptr %r4, align 8
  %writeInteger_arg24 = load i32, ptr %r_load23, align 4
  call void @writeInteger(i32 %writeInteger_arg24)
  call void @writeString(ptr @global_str.14)
  %arr_arrayptr = load ptr, ptr %arr1, align 8
  %elementptr25 = getelementptr i8, ptr %arr_arrayptr, i32 5
  %left_load26 = load i8, ptr %elementptr25, align 1
  %eqtmp = icmp eq i8 %left_load26, 97
  %0 = zext i1 %eqtmp to i32
  %if_cond = icmp ne i32 %0, 0
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %innerIncrement_entry
  call void @writeString(ptr @global_str.15)
  %arr_arrayptr27 = load ptr, ptr %arr1, align 8
  %elementptr28 = getelementptr i8, ptr %arr_arrayptr27, i32 5
  %writeChar_arg = load i8, ptr %elementptr28, align 1
  call void @writeChar(i8 %writeChar_arg)
  call void @writeString(ptr @global_str.16)
  %arr_arrayptr29 = load ptr, ptr %arr1, align 8
  %elementptr30 = getelementptr i8, ptr %arr_arrayptr29, i32 5
  store i8 98, ptr %elementptr30, align 1
  br label %ifcont

else:                                             ; preds = %innerIncrement_entry
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  ret void
}

define void @foo(ptr %closure) {
foo_entry:
  %arr_ptr = getelementptr inbounds %foo_closure, ptr %closure, i32 0, i32 0
  %arr = load ptr, ptr %arr_ptr, align 8
  %arr1 = alloca ptr, align 8
  store ptr %arr, ptr %arr1, align 8
  %v_ptr = getelementptr inbounds %foo_closure, ptr %closure, i32 0, i32 1
  %v = load ptr, ptr %v_ptr, align 8
  %v2 = alloca ptr, align 8
  store ptr %v, ptr %v2, align 8
  %u_ptr = getelementptr inbounds %foo_closure, ptr %closure, i32 0, i32 2
  %u = load ptr, ptr %u_ptr, align 8
  %u3 = alloca ptr, align 8
  store ptr %u, ptr %u3, align 8
  %r_ptr = getelementptr inbounds %foo_closure, ptr %closure, i32 0, i32 3
  %r = load ptr, ptr %r_ptr, align 8
  %r4 = alloca ptr, align 8
  store ptr %r, ptr %r4, align 8
  %r_load = load ptr, ptr %r4, align 8
  %left_load = load i32, ptr %r_load, align 4
  %addtmp = add i32 %left_load, 7
  %r_load5 = load ptr, ptr %r4, align 8
  store i32 %addtmp, ptr %r_load5, align 4
  %u_load = load ptr, ptr %u3, align 8
  %left_load6 = load i32, ptr %u_load, align 4
  %addtmp7 = add i32 %left_load6, 1
  %u_load8 = load ptr, ptr %u3, align 8
  store i32 %addtmp7, ptr %u_load8, align 4
  call void @writeString(ptr @global_str)
  %u_load9 = load ptr, ptr %u3, align 8
  %writeInteger_arg = load i32, ptr %u_load9, align 4
  call void @writeInteger(i32 %writeInteger_arg)
  call void @writeString(ptr @global_str.2)
  %v_arrayptr = load ptr, ptr %v2, align 8
  %elementptr = getelementptr i32, ptr %v_arrayptr, i32 5
  %left_load10 = load i32, ptr %elementptr, align 4
  %addtmp11 = add i32 %left_load10, 1
  %v_arrayptr12 = load ptr, ptr %v2, align 8
  %elementptr13 = getelementptr i32, ptr %v_arrayptr12, i32 5
  store i32 %addtmp11, ptr %elementptr13, align 4
  call void @writeString(ptr @global_str.3)
  %v_arrayptr14 = load ptr, ptr %v2, align 8
  %elementptr15 = getelementptr i32, ptr %v_arrayptr14, i32 5
  %writeInteger_arg16 = load i32, ptr %elementptr15, align 4
  call void @writeInteger(i32 %writeInteger_arg16)
  call void @writeString(ptr @global_str.4)
  call void @writeString(ptr @global_str.5)
  %r_load17 = load ptr, ptr %r4, align 8
  %writeInteger_arg18 = load i32, ptr %r_load17, align 4
  call void @writeInteger(i32 %writeInteger_arg18)
  call void @writeString(ptr @global_str.6)
  %arr_arrayptr = load ptr, ptr %arr1, align 8
  %elementptr19 = getelementptr i8, ptr %arr_arrayptr, i32 5
  store i8 97, ptr %elementptr19, align 1
  call void @writeString(ptr @global_str.7)
  %arr_arrayptr20 = load ptr, ptr %arr1, align 8
  %elementptr21 = getelementptr i8, ptr %arr_arrayptr20, i32 5
  %writeChar_arg = load i8, ptr %elementptr21, align 1
  call void @writeChar(i8 %writeChar_arg)
  call void @writeString(ptr @global_str.8)
  ret void
}
