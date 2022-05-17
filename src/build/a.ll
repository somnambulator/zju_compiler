; ModuleID = 'Code Gen'
source_filename = "Code Gen"

@printfomat = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @fib(i32 %a) {
entry:
  %a1 = alloca i32, align 4
  store i32 %a, i32* %a1, align 4
  %a2 = load i32, i32* %a1, align 4
  %cmptmp = icmp eq i32 %a2, 1
  %ifcond = icmp ne i1 %cmptmp, false
  br i1 %ifcond, label %then, label %else

then:                                             ; preds = %entry
  ret i32 1

after_ret:                                        ; No predecessors!
  br label %ifcont14

else:                                             ; preds = %entry
  %a3 = load i32, i32* %a1, align 4
  %cmptmp4 = icmp eq i32 %a3, 2
  %ifcond5 = icmp ne i1 %cmptmp4, false
  br i1 %ifcond5, label %then6, label %else8

then6:                                            ; preds = %else
  ret i32 2

after_ret7:                                       ; No predecessors!
  br label %ifcont

else8:                                            ; preds = %else
  %a9 = load i32, i32* %a1, align 4
  %subtmp = sub i32 %a9, 1
  %calltmp = call i32 @fib(i32 %subtmp)
  %a10 = load i32, i32* %a1, align 4
  %subtmp11 = sub i32 %a10, 2
  %calltmp12 = call i32 @fib(i32 %subtmp11)
  %addtmp = add i32 %calltmp, %calltmp12
  ret i32 %addtmp

after_ret13:                                      ; No predecessors!
  br label %ifcont

ifcont:                                           ; preds = %after_ret13, %after_ret7
  %iftmp = phi i32 [ 2, %after_ret7 ], [ %addtmp, %after_ret13 ]
  br label %ifcont14

ifcont14:                                         ; preds = %ifcont, %after_ret
  %iftmp15 = phi i32 [ 1, %after_ret ], [ %iftmp, %ifcont ]
  ret i32 0
}

define i32 @main() {
entry:
  %a = alloca i32, align 4
  store i32 0, i32* %a, align 4
  store i32 9, i32* %a, align 4
  %a1 = load i32, i32* %a, align 4
  %calltmp = call i32 @fib(i32 %a1)
  %printtmp = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printfomat, i32 0, i32 0), i32 %calltmp)
  ret i32 0
}

declare i32 @printf(i8*, ...)
