% Limpar variáveis e fechar figuras
clear;
clc;
close all;

% Parâmetros DH do robô
a = [0, 95, 95, 95];        % Comprimento dos elos (em mm)
alpha = [pi/2, 0, 0, 0];    % Ângulo de rotação entre os eixos Z dos elos
d = [70, 0, 0, 0];          % Deslocamento ao longo do eixo Z (em mm)
theta = [0, 70, -60, -30] * pi / 180;  % Ângulo de rotação inicial em relação ao eixo X atual (convertido para radianos)

% Criação do objeto de robô com os elos definidos
robot = SerialLink([ 
    Revolute('d', d(1), 'a', a(1), 'alpha', alpha(1), 'qlim', [0 2*pi]),   % Elo 1 (vertical)
    Revolute('d', d(2), 'a', a(2), 'alpha', alpha(2), 'qlim', [0 2*pi]),   % Elo 2 (horizontal)
    Revolute('d', d(3), 'a', a(3), 'alpha', alpha(3), 'qlim', [0 2*pi]),   % Elo 3 (horizontal)
    Revolute('d', d(4), 'a', a(4), 'alpha', alpha(4), 'qlim', [0 2*pi])    % Elo 4 (horizontal)
], 'name', 'Robo');

% Cálculo da cinemática direta (transformação homogênea) do robô
T_total = eye(4); % Inicializar a matriz identidade para o cálculo da transformação total

% Calcular a matriz de transformação para cada junta
for i = 1:4
    % Calculando a matriz de transformação homogênea T_i para cada junta usando os parâmetros DH
    T_i = [cos(theta(i)), -sin(theta(i))*cos(alpha(i)), sin(theta(i))*sin(alpha(i)), a(i)*cos(theta(i));
           sin(theta(i)), cos(theta(i))*cos(alpha(i)), -cos(theta(i))*sin(alpha(i)), a(i)*sin(theta(i));
           0, sin(alpha(i)), cos(alpha(i)), d(i);
           0, 0, 0, 1];
    
    % Multiplicar a matriz de transformação atual com a transformação total
    T_total = T_total * T_i;
    
    % Exibir a matriz de transformação para a junta i
    fprintf('Matriz de Transformação Homogênea T_%d:\n', i);
    disp(T_i);
end

% Exibir a matriz de transformação total
fprintf('Matriz de Transformação Total T_total:\n');
disp(T_total);

% Plot do robô na configuração especificada
figure;
robot.plot(theta);



