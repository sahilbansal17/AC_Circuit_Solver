for testCase in Public_cases/solveCases/*.cir
	do
        echo "========================================================================================================================"
		echo $testCase
		./ac_circuit_solver $testCase $testCase.svg $testCase.txt
        echo  "========================================================================================================================"
    done 