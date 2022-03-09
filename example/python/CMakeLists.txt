set(PY_SOURCES mean.py var.py autocorr.py batch.py)
foreach(name ${PY_SOURCES})
  configure_file(${name} ${name} COPYONLY)
endforeach(name ${PY_SOURCES})
