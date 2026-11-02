// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract BankAccount {

    mapping(address => uint256) private balances;

    function deposit() public payable {
        require(msg.value > 0, "Send some Ether");
        balances[msg.sender] += msg.value;
    }

    function withdraw(uint256 amount) public {
        require(amount <= balances[msg.sender], "Insufficient balance");
        balances[msg.sender] -= amount;
        payable(msg.sender).transfer(amount);
    }

    function getBalance() public view returns (uint256) {
        return balances[msg.sender];
    }
}