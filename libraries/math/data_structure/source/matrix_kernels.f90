module matrix_kernels
    use iso_c_binding
    implicit none

contains
    subroutine fortran_matmul_double(A, ra, ca, B, cb, C) bind(C, name="fortran_matmul_double")
        integer(c_size_t), value :: ra, ca, cb
        real(c_double), intent(in)  :: A(ca, ra)  
        real(c_double), intent(in)  :: B(cb, ca)  
        real(c_double), intent(out) :: C(cb, ra) 
        C = matmul(A, B)
    end subroutine

    subroutine fortran_matmul_float(A, ra, ca, B, cb, C) bind(C, name="fortran_matmul_float")
        integer(c_size_t), value :: ra, ca, cb
        real(c_float), intent(in)  :: A(ca, ra)  
        real(c_float), intent(in)  :: B(cb, ca)  
        real(c_float), intent(out) :: C(cb, ra) 
        C = matmul(A, B)
    end subroutine

end module