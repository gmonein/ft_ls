echo "" > my_test
echo "" > ls_test
ls -rt > ls_test
../ft_ls -rt > my_test
diff ls_test my_test
rm -rf my_test ls_test
