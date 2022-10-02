(defpackage :sbcl-fifo
  (:use :cl)
  (:export :run :send))
(in-package :sbcl-fifo)

(defun send (msg)
  (with-open-file (fifo "./fifo-test"
                        :direction :output
                        :if-exists :supersede)
    (format fifo msg)))

(defun run ()
  (send "oh hi"))

(defpackage :main
  (:use :cl :sbcl-fifo))
(in-package :main)
(sbcl-fifo:run)
