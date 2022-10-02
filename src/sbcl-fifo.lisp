(defpackage :sbcl-fifo
  (:use :cl)
  (:export :run))
(in-package :sbcl-fifo)

(defun run ()
  (with-open-file (fifo "/tmp/fifo-test" :if-does-not-exist :create)
    (loop
      (when (or (listen fifo)
                (progn (sleep 0.1)
                       (listen fifo)))
        (format t "From C: ~A~%" (read-line fifo))))))

(defpackage :main
  (:use :cl :sbcl-fifo))
(in-package :main)
(sbcl-fifo:run)
