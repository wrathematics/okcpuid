cpu_id <- function()
{
  ret <- .Call(Rcpuid_cpuid)
  
  return( ret )
}



cpu_ins <- function(ret.logical=FALSE)
{
  ret <- .Call(Rcpuid_available_instructions)
  
  if (ret.logical)
    ret <- sapply(ret, function(i) if (i=="present") TRUE else FALSE)
  
  return( ret )
}



cpu_clock <- function()
{
  ret <- .Call(Rcpuid_cpuid_info)
  
  class(ret$clock.os) <- "MHz"
  class(ret$clock.tested) <- "MHz"
  
  ret$peak <- flops(size=ret$peak*1e6, unit="mflops")
  
  return( ret )
}

