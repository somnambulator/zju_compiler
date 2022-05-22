; ModuleID = 'Code Gen'
source_filename = "Code Gen"

@strtype = external global [256 x i8]
@printfomat = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@readfomat = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@printfomat.1 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@readfomat.2 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@printfomat.3 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@printfomat.4 = private unnamed_addr constant [5 x i8] c"%d%s\00", align 1

define i32 @partition(i32 %high, i32 %low, i32* %a) {
entry:
  %key = alloca i32, align 4
  %a3 = alloca i32*, align 8
  %low2 = alloca i32, align 4
  %high1 = alloca i32, align 4
  store i32 %high, i32* %high1, align 4
  store i32 %low, i32* %low2, align 4
  store i32* %a, i32** %a3, align 8
  store i32 0, i32* %key, align 4
  %low4 = load i32, i32* %low2, align 4
  %arrayele = getelementptr inbounds i32, i32* %a, i32 %low4
  %arrayElement = load i32, i32* %arrayele, align 4
  store i32 %arrayElement, i32* %key, align 4
  br label %CondBB

CondBB:                                           ; preds = %ifcont57, %entry
  %low5 = load i32, i32* %low2, align 4
  %high6 = load i32, i32* %high1, align 4
  %cmptmp = icmp slt i32 %low5, %high6
  %loopcond = icmp ne i1 %cmptmp, false
  br i1 %loopcond, label %loop, label %afterloop
  br label %loop

loop:                                             ; preds = %CondBB, %CondBB
  br label %CondBB7

afterloop:                                        ; preds = %CondBB
  %loopexit59 = phi i32 [ 0, %CondBB ], [ 0, %ifcont57 ]
  %low60 = load i32, i32* %low2, align 4
  %arrayele61 = getelementptr inbounds i32, i32* %a, i32 %low60
  %key62 = load i32, i32* %key, align 4
  store i32 %key62, i32* %arrayele61, align 4
  %low63 = load i32, i32* %low2, align 4
  ret i32 %low63

CondBB7:                                          ; preds = %loop8, %loop
  %low10 = load i32, i32* %low2, align 4
  %high11 = load i32, i32* %high1, align 4
  %cmptmp12 = icmp slt i32 %low10, %high11
  %high13 = load i32, i32* %high1, align 4
  %arrayele14 = getelementptr inbounds i32, i32* %a, i32 %high13
  %arrayElementValue = load i32, i32* %arrayele14, align 4
  %key15 = load i32, i32* %key, align 4
  %cmptmp16 = icmp sge i32 %arrayElementValue, %key15
  %andtmp = and i1 %cmptmp12, %cmptmp16
  %loopcond17 = icmp ne i1 %andtmp, false
  br i1 %loopcond17, label %loop8, label %afterloop9
  br label %loop8

loop8:                                            ; preds = %CondBB7, %CondBB7
  %high18 = load i32, i32* %high1, align 4
  %subtmp = sub i32 %high18, 1
  store i32 %subtmp, i32* %high1, align 4
  br label %CondBB7

afterloop9:                                       ; preds = %CondBB7
  %loopexit = phi i32 [ 0, %CondBB7 ], [ 0, %loop8 ]
  %low19 = load i32, i32* %low2, align 4
  %high20 = load i32, i32* %high1, align 4
  %cmptmp21 = icmp slt i32 %low19, %high20
  %ifcond = icmp ne i1 %cmptmp21, false
  br i1 %ifcond, label %then, label %else

then:                                             ; preds = %afterloop9
  %low22 = load i32, i32* %low2, align 4
  %arrayele23 = getelementptr inbounds i32, i32* %a, i32 %low22
  %high24 = load i32, i32* %high1, align 4
  %arrayele25 = getelementptr inbounds i32, i32* %a, i32 %high24
  %arrayElement26 = load i32, i32* %arrayele25, align 4
  store i32 %arrayElement26, i32* %arrayele23, align 4
  %low27 = load i32, i32* %low2, align 4
  %addtmp = add i32 %low27, 1
  store i32 %addtmp, i32* %low2, align 4
  br label %ifcont

else:                                             ; preds = %afterloop9
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %iftmp = phi i32 [ 0, %then ], [ 0, %else ]
  br label %CondBB28

CondBB28:                                         ; preds = %loop29, %ifcont
  %low31 = load i32, i32* %low2, align 4
  %high32 = load i32, i32* %high1, align 4
  %cmptmp33 = icmp slt i32 %low31, %high32
  %low34 = load i32, i32* %low2, align 4
  %arrayele35 = getelementptr inbounds i32, i32* %a, i32 %low34
  %arrayElementValue36 = load i32, i32* %arrayele35, align 4
  %key37 = load i32, i32* %key, align 4
  %cmptmp38 = icmp sle i32 %arrayElementValue36, %key37
  %andtmp39 = and i1 %cmptmp33, %cmptmp38
  %loopcond40 = icmp ne i1 %andtmp39, false
  br i1 %loopcond40, label %loop29, label %afterloop30
  br label %loop29

loop29:                                           ; preds = %CondBB28, %CondBB28
  %low41 = load i32, i32* %low2, align 4
  %addtmp42 = add i32 %low41, 1
  store i32 %addtmp42, i32* %low2, align 4
  br label %CondBB28

afterloop30:                                      ; preds = %CondBB28
  %loopexit43 = phi i32 [ 0, %CondBB28 ], [ 0, %loop29 ]
  %low44 = load i32, i32* %low2, align 4
  %high45 = load i32, i32* %high1, align 4
  %cmptmp46 = icmp slt i32 %low44, %high45
  %ifcond47 = icmp ne i1 %cmptmp46, false
  br i1 %ifcond47, label %then48, label %else56

then48:                                           ; preds = %afterloop30
  %high49 = load i32, i32* %high1, align 4
  %arrayele50 = getelementptr inbounds i32, i32* %a, i32 %high49
  %low51 = load i32, i32* %low2, align 4
  %arrayele52 = getelementptr inbounds i32, i32* %a, i32 %low51
  %arrayElement53 = load i32, i32* %arrayele52, align 4
  store i32 %arrayElement53, i32* %arrayele50, align 4
  %high54 = load i32, i32* %high1, align 4
  %subtmp55 = sub i32 %high54, 1
  store i32 %subtmp55, i32* %high1, align 4
  br label %ifcont57

else56:                                           ; preds = %afterloop30
  br label %ifcont57

ifcont57:                                         ; preds = %else56, %then48
  %iftmp58 = phi i32 [ 0, %then48 ], [ 0, %else56 ]
  br label %CondBB
}

define i32 @quicksort(i32 %end, i32 %start, i32* %a) {
entry:
  %pos = alloca i32, align 4
  %a3 = alloca i32*, align 8
  %start2 = alloca i32, align 4
  %end1 = alloca i32, align 4
  store i32 %end, i32* %end1, align 4
  store i32 %start, i32* %start2, align 4
  store i32* %a, i32** %a3, align 8
  store i32 0, i32* %pos, align 4
  %start4 = load i32, i32* %start2, align 4
  %end5 = load i32, i32* %end1, align 4
  %cmptmp = icmp slt i32 %start4, %end5
  %ifcond = icmp ne i1 %cmptmp, false
  br i1 %ifcond, label %then, label %else

then:                                             ; preds = %entry
  %end6 = load i32, i32* %end1, align 4
  %start7 = load i32, i32* %start2, align 4
  %arrayStartAddr = getelementptr inbounds i32, i32* %a, i32 0
  %arrayele = getelementptr inbounds i32, i32* %a, i32 0
  %calltmp = call i32 @partition(i32 %end6, i32 %start7, i32* %arrayele)
  store i32 %calltmp, i32* %pos, align 4
  %pos8 = load i32, i32* %pos, align 4
  %subtmp = sub i32 %pos8, 1
  %start9 = load i32, i32* %start2, align 4
  %arrayStartAddr10 = getelementptr inbounds i32, i32* %a, i32 0
  %arrayele11 = getelementptr inbounds i32, i32* %a, i32 0
  %calltmp12 = call i32 @quicksort(i32 %subtmp, i32 %start9, i32* %arrayele11)
  %end13 = load i32, i32* %end1, align 4
  %pos14 = load i32, i32* %pos, align 4
  %addtmp = add i32 %pos14, 1
  %arrayStartAddr15 = getelementptr inbounds i32, i32* %a, i32 0
  %arrayele16 = getelementptr inbounds i32, i32* %a, i32 0
  %calltmp17 = call i32 @quicksort(i32 %end13, i32 %addtmp, i32* %arrayele16)
  br label %ifcont

else:                                             ; preds = %entry
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %iftmp = phi i32 [ 0, %then ], [ 0, %else ]
  ret i32 0
}

define i32 @main() {
entry:
  %a = alloca [10000 x i32], align 4
  %n = alloca i32, align 4
  %j = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %i, align 4
  store i32 0, i32* %j, align 4
  store i32 0, i32* %n, align 4
  %ElementwiseAddr = bitcast [10000 x i32]* %a to i32*
  %0 = alloca [256 x i8], i64 ptrtoint ([256 x i8]* getelementptr ([256 x i8], [256 x i8]* null, i32 1) to i64), align 1
  %strtmp = getelementptr [256 x i8], [256 x i8]* %0, i32 0
  store [256 x i8] c"Please enter n:\0A\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", [256 x i8]* %strtmp, align 1
  %printtmp = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @printfomat, i32 0, i32 0), [256 x i8]* %0)
  %readtmp = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @readfomat, i32 0, i32 0), i32* %n)
  %n1 = load i32, i32* %n, align 4
  %cmptmp = icmp eq i32 %n1, 0
  %ifcond = icmp ne i1 %cmptmp, false
  br i1 %ifcond, label %then, label %else

then:                                             ; preds = %entry
  ret i32 0

after_ret:                                        ; No predecessors!
  br label %ifcont

else:                                             ; preds = %entry
  br label %ifcont

ifcont:                                           ; preds = %else, %after_ret
  %iftmp = phi i32 [ 0, %after_ret ], [ 0, %else ]
  %1 = alloca [256 x i8], i64 ptrtoint ([256 x i8]* getelementptr ([256 x i8], [256 x i8]* null, i32 1) to i64), align 1
  %strtmp2 = getelementptr [256 x i8], [256 x i8]* %1, i32 0
  store [256 x i8] c"Please enter the array:\0A\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", [256 x i8]* %strtmp2, align 1
  %printtmp3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @printfomat.1, i32 0, i32 0), [256 x i8]* %1)
  store i32 0, i32* %i, align 4
  br label %loop

loop:                                             ; preds = %loop, %ifcont
  %loopentry = phi i32 [ 0, %ifcont ], [ 0, %loop ]
  %i4 = load i32, i32* %i, align 4
  %arrayele = getelementptr inbounds i32, i32* %ElementwiseAddr, i32 %i4
  %readtmp5 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @readfomat.2, i32 0, i32 0), i32* %arrayele)
  %i6 = load i32, i32* %i, align 4
  %addtmp = add i32 %i6, 1
  store i32 %addtmp, i32* %i, align 4
  %i7 = load i32, i32* %i, align 4
  %n8 = load i32, i32* %n, align 4
  %cmptmp9 = icmp slt i32 %i7, %n8
  %loopcond = icmp ne i1 %cmptmp9, false
  br i1 %loopcond, label %loop, label %afterloop

afterloop:                                        ; preds = %loop
  %n10 = load i32, i32* %n, align 4
  %subtmp = sub i32 %n10, 1
  %arrayStartAddr = getelementptr inbounds i32, i32* %ElementwiseAddr, i32 0
  %arrayele11 = getelementptr inbounds i32, i32* %ElementwiseAddr, i32 0
  %calltmp = call i32 @quicksort(i32 %subtmp, i32 0, i32* %arrayele11)
  %2 = alloca [256 x i8], i64 ptrtoint ([256 x i8]* getelementptr ([256 x i8], [256 x i8]* null, i32 1) to i64), align 1
  %strtmp12 = getelementptr [256 x i8], [256 x i8]* %2, i32 0
  store [256 x i8] c"The result is:\0A\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", [256 x i8]* %strtmp12, align 1
  %printtmp13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @printfomat.3, i32 0, i32 0), [256 x i8]* %2)
  store i32 0, i32* %i, align 4
  br label %loop14

loop14:                                           ; preds = %loop14, %afterloop
  %loopentry15 = phi i32 [ 0, %afterloop ], [ 0, %loop14 ]
  %i16 = load i32, i32* %i, align 4
  %arrayele17 = getelementptr inbounds i32, i32* %ElementwiseAddr, i32 %i16
  %arrayelement = load i32, i32* %arrayele17, align 4
  %3 = alloca [256 x i8], i64 ptrtoint ([256 x i8]* getelementptr ([256 x i8], [256 x i8]* null, i32 1) to i64), align 1
  %strtmp18 = getelementptr [256 x i8], [256 x i8]* %3, i32 0
  store [256 x i8] c"\0A\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", [256 x i8]* %strtmp18, align 1
  %printtmp19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @printfomat.4, i32 0, i32 0), i32 %arrayelement, [256 x i8]* %3)
  %i20 = load i32, i32* %i, align 4
  %addtmp21 = add i32 %i20, 1
  store i32 %addtmp21, i32* %i, align 4
  %i22 = load i32, i32* %i, align 4
  %n23 = load i32, i32* %n, align 4
  %cmptmp24 = icmp slt i32 %i22, %n23
  %loopcond25 = icmp ne i1 %cmptmp24, false
  br i1 %loopcond25, label %loop14, label %afterloop26

afterloop26:                                      ; preds = %loop14
  ret i32 0
}

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)
