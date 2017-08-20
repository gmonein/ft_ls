echo "" > my_test
echo "" > ls_test
ls -Rt > ls_test
./ft_ls -Rt > my_test
diff ls_test my_test
