# foodconserve-manager
Logistics and client management system for a food preservation company. Includes modules for tracking deliveries, managing staff, and client databases. Built with C++ and Qt for clean and efficient workflow handling.


# Employee and Client Management with Delivery Tracking and RFID Door Access

## Description

This software is designed to manage employees, track client deliveries, and control door access using RFID codes. The system is divided into separate modules for client management and delivery tracking, while integrating RFID technology to secure door access for employees.

## Features

### Employee Management
- Add, update, and remove Employee profiles.
- Store Employee contact details .


### Client Management
- Add, update, and remove client profiles.
- Store client contact details and delivery preferences.
- Track client delivery history and preferences.
- Generate reports on Client Management.
- Authentication: Employees must log in with a username and password to access the system.
- **Password Management**:
          - Forgot Password: Employees can recover their account by resetting their password through a secure process (e.g., email verification).
          - Password Encryption: All passwords are securely encrypted to protect sensitive information.
  

### Delivery Management
- Manage delivery tasks, including assignment to employees.
- Track the status of each delivery (pending, in-progress, completed).
- Generate reports on delivery statuses and performance.
- Track  delivery history.

### RFID Door Access
- Secure door access via RFID codes for authorized employees.
- Employees can open doors at delivery locations or facilities using RFID scanning.
- Access control system to ensure that only authorized personnel can unlock doors.

### Notifications
- Send notifications for delivery updates and access attempts.
- Alerts when deliveries are completed or when there are issues with access.

### Reporting
- Generate detailed reports for both client deliveries and employee performance.
- Report on delivery times, access control logs, and client interactions.

## Installation

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/minach19/foodconserve-manager.git
