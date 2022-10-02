(defpackage :sbcl-fifo
  (:use :cl)
  (:export :run :send))
(in-package :sbcl-fifo)

(defun send (msg)
  (with-open-file (fifo "./pipe-test"
                        :direction :output
                        :if-exists :supersede)
    (format fifo msg)))

(defun run ()
  (send "2 12 30 50"))

(defpackage :main
  (:use :cl :sbcl-fifo))
(in-package :main)
(sbcl-fifo:run)
