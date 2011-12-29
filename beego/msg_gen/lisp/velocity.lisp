; Auto-generated. Do not edit!


(cl:in-package beego-msg)


;//! \htmlinclude velocity.msg.html

(cl:defclass <velocity> (roslisp-msg-protocol:ros-message)
  ((trans_vel
    :reader trans_vel
    :initarg :trans_vel
    :type cl:float
    :initform 0.0)
   (rot_vel
    :reader rot_vel
    :initarg :rot_vel
    :type cl:float
    :initform 0.0))
)

(cl:defclass velocity (<velocity>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <velocity>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'velocity)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name beego-msg:<velocity> is deprecated: use beego-msg:velocity instead.")))

(cl:ensure-generic-function 'trans_vel-val :lambda-list '(m))
(cl:defmethod trans_vel-val ((m <velocity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beego-msg:trans_vel-val is deprecated.  Use beego-msg:trans_vel instead.")
  (trans_vel m))

(cl:ensure-generic-function 'rot_vel-val :lambda-list '(m))
(cl:defmethod rot_vel-val ((m <velocity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beego-msg:rot_vel-val is deprecated.  Use beego-msg:rot_vel instead.")
  (rot_vel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <velocity>) ostream)
  "Serializes a message object of type '<velocity>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'trans_vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rot_vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <velocity>) istream)
  "Deserializes a message object of type '<velocity>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'trans_vel) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rot_vel) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<velocity>)))
  "Returns string type for a message object of type '<velocity>"
  "beego/velocity")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'velocity)))
  "Returns string type for a message object of type 'velocity"
  "beego/velocity")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<velocity>)))
  "Returns md5sum for a message object of type '<velocity>"
  "a9a36d4aead03174102ed0f5686cc73d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'velocity)))
  "Returns md5sum for a message object of type 'velocity"
  "a9a36d4aead03174102ed0f5686cc73d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<velocity>)))
  "Returns full string definition for message of type '<velocity>"
  (cl:format cl:nil "float32 trans_vel~%float32 rot_vel~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'velocity)))
  "Returns full string definition for message of type 'velocity"
  (cl:format cl:nil "float32 trans_vel~%float32 rot_vel~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <velocity>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <velocity>))
  "Converts a ROS message object to a list"
  (cl:list 'velocity
    (cl:cons ':trans_vel (trans_vel msg))
    (cl:cons ':rot_vel (rot_vel msg))
))
