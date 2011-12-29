FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/beego/msg"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/velocity.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_velocity.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
