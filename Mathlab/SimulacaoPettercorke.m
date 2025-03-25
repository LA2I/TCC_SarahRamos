% Limpar vari�veis e fechar figuras
clear;
clc;
close all;

% Par�metros DH do rob�
a = [0, 95, 95, 95];        % Comprimento dos elos (em mm)
alpha = [pi/2, 0, 0, 0];    % �ngulo de rota��o entre os eixos Z dos elos
d = [70, 0, 0, 0];          % Deslocamento ao longo do eixo Z (em mm)
theta = [0, 0, 0, 0];       % �ngulo de rota��o inicial em rela��o ao eixo X atual

% Cria��o do objeto de rob� com os elos definidos
robot = SerialLink([ 
    Revolute('d', d(1), 'a', a(1), 'alpha', alpha(1), 'qlim', [0 2*pi]),   % Elo 1 (vertical)
    Revolute('d', d(2), 'a', a(2), 'alpha', alpha(2), 'qlim', [0 2*pi]),   % Elo 2 (horizontal)
    Revolute('d', d(3), 'a', a(3), 'alpha', alpha(3), 'qlim', [0 2*pi]),   % Elo 3 (horizontal)
    Revolute('d', d(4), 'a', a(4), 'alpha', alpha(4), 'qlim', [0 2*pi])    % Elo 4 (horizontal)
], 'name', 'Robo');

% Plot do rob� na configura��o inicial
figure;
robot.plot(theta);

% Ajustar os limites do gr�fico para n�o mostrar valores abaixo de 0 no eixo Z
ax = gca;  % Obter o objeto de eixo atual
ax.ZLim = [0, ax.ZLim(2)];  % Definir o limite inferior do eixo Z como 0

% C�lculo das matrizes de transforma��o homog�nea para cada junta
T_total = eye(4); % Inicializar a matriz identidade para o c�lculo da transforma��o total

for i = 1:4
    % Calculando a matriz de transforma��o homog�nea T_i para cada junta usando os par�metros DH
    T_i = [cos(theta(i)), -sin(theta(i))*cos(alpha(i)), sin(theta(i))*sin(alpha(i)), a(i)*cos(theta(i));
           sin(theta(i)), cos(theta(i))*cos(alpha(i)), -cos(theta(i))*sin(alpha(i)), a(i)*sin(theta(i));
           0, sin(alpha(i)), cos(alpha(i)), d(i);
           0, 0, 0, 1];
    
    % Multiplicar a matriz de transforma��o atual com a transforma��o total
    T_total = T_total * T_i;
    
    % Exibir a matriz de transforma��o para a junta i
    fprintf('Matriz de Transforma��o Homog�nea T_%d:\n', i);
    disp(T_i);
end

% Exibir a matriz de transforma��o total
fprintf('Matriz de Transforma��o Total T_total:\n');
disp(T_total);

% Limites das juntas (em radianos)
joint_limits = [-pi/2, pi/2;   % Junta 1: -90 a 90 graus
                -pi/1, pi/1;   % Junta 2: -90 a 90 graus
                -pi/2, pi/2;   % Junta 3: -90 a 90 graus
                -pi/2, pi/2];  % Junta 4: -90 a 90 graus

% Valores iniciais das juntas (meio do intervalo)
initial_values = [0, 0, 0, 0];

% Criar sliders para cada junta com limites e valores iniciais definidos
for i = 1:4
    uicontrol('Style', 'slider', 'Min', joint_limits(i, 1), 'Max', joint_limits(i, 2), 'Value', initial_values(i), ...
        'Position', [20, 20 + (i-1)*40, 200, 20], ...
        'Callback', @(src, event) update_robot_joints(robot, i, src.Value));
end

% Fun��o para atualizar as juntas do rob�
function update_robot_joints(robot, joint_index, joint_value)
    % Obter a configura��o atual das juntas
    q = robot.getpos();
    
    % Atualizar o valor da junta espec�fica
    q(joint_index) = joint_value;
    
    % Atualizar a posi��o do rob�
    robot.plot(q);
    
    % Ajustar novamente os limites do eixo Z ap�s cada atualiza��o
    ax = gca;  % Obter o objeto de eixo atual
    ax.ZLim = [0, ax.ZLim(2)];  % Garantir que o limite inferior do eixo Z continue sendo 0
end

% Fun��o para calcular e exibir os �ngulos das juntas
function calcular_angulos(robot)
    % Obter a configura��o final das juntas
    q_final = robot.getpos();
    
    % Exibir os �ngulos das juntas no formato [q1, q2, q3, q4]
    fprintf('�ngulos das juntas: [%.4f, %.4f, %.4f, %.4f]\n', q_final(1), q_final(2), q_final(3), q_final(4));
end
