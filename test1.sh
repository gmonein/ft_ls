echo "" > my_test
echo "" > ls_test
ls -Rtf | cat -e > ls_test
./ft_ls -Rtf | cat > my_test
diff ls_test my_test
