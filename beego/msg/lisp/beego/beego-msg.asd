
(in-package :asdf)

(defsystem "beego-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils)
  :components ((:file "_package")
    (:file "velocity" :depends-on ("_package"))
    (:file "_package_velocity" :depends-on ("_package"))
    ))
