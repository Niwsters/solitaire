(defpackage :sbcl-fifo
  (:use :cl)
  (:export :run :send))
(in-package :sbcl-fifo)

(defun suit-to-num (suit)
  (case suit
    (:clubs 0)
    (:diamonds 1)
    (:hearts 2)
    (:spades 3)))

(defun value-to-num (value)
  (case value
    (:ace 0)
    (:two 1)
    (:three 2)
    (:four 3)
    (:five 4)
    (:six 5)
    (:seven 6)
    (:eight 7)
    (:nine 8)
    (:ten 9)
    (:jack 10)
    (:queen 11)
    (:king 12)))

(defun send (msg)
  (with-open-file (fifo "./pipe-test"
                        :direction :output
                        :if-exists :supersede)
    (format fifo msg)))

(defun send-card (suit value)
  (send
    (concatenate
      'string
      (write-to-string (suit-to-num suit))
      " "
      (write-to-string (value-to-num value))
      " 30 50")))
