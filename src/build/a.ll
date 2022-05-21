; ModuleID = 'Code Gen'
source_filename = "Code Gen"

@strtype = external global [256 x i8]
@readfomat = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@printfomat = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() {
entry:
  %a = alloca [10 x i32], align 4
  %ElementwiseAddr = bitcast [10 x i32]* %a to i32*
  %arrayele = getelementptr inbounds i32, i32* %ElementwiseAddr, i32 2
  %readtmp = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @readfomat, i32 0, i32 0), i32* %arrayele)
  %arrayele1 = getelementptr inbounds i32, i32* %ElementwiseAddr, i32 2
  %arrayelement = load i32, i32* %arrayele1, align 4
  %printtmp = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printfomat, i32 0, i32 0), i32 %arrayelement)
  ret i32 0
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
