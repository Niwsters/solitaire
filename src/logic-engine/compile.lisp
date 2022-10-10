(require 'cmp)

(compile-file "src/logic-engine/logic.lisp" :system-p t)
(compile-file "src/logic-engine/main.lisp" :system-p t)

(c:build-program
  "bin/logic"
  :lisp-files '("src/logic-engine/main.o"))

(quit)
