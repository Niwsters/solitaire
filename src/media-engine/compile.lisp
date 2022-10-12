; generate test.o
(compile-file "test_a.lisp" :system-p t)

; generate test.a
(c:build-static-library "test"
                        :lisp-files '("test_a.o")
                        :init-name "init_test")

(quit)
