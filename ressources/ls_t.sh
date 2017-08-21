echo "" > my_test
echo "" > ls_test
ls -t > ls_test
../ft_ls -t > my_test
diff ls_test my_test
