echo "" > my_test
echo "" > ls_test
ls -Rrt > ls_test
../ft_ls -Rrt > my_test
diff ls_test my_test
rm -rf my_test ls_test
