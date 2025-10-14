/*****************/
/* Custom Region */
/*****************/

// input wire xa_p0;
// input wire xa_n0;
// wire clk_system;
// wire clk_dca_core;
// wire clk_core;
// wire clk_system_external;
// wire clk_system_debug;
// wire clk_local_access;
// wire clk_process_000;
// wire clk_process_001;
// wire clk_dram_if;
// wire clk_dram_sys;
// wire clk_dram_ref;
// wire clk_noc;
// wire gclk_system;
// wire gclk_dca_core;
// wire gclk_core;
// wire gclk_system_external;
// wire gclk_system_debug;
// wire gclk_local_access;
// wire gclk_process_000;
// wire gclk_process_001;
// wire gclk_noc;
// wire tick_1us;
// wire tick_62d5ms;
// wire tick_gpio;
// wire spi_common_sclk;
// wire spi_common_sdq0;
// wire global_rstnn;
// wire global_rstpp;
// wire [(8)-1:0] rstnn_seqeunce;
// wire [(8)-1:0] rstpp_seqeunce;
// wire rstnn_user;
// wire rstpp_user;
// wire i_xadc_wiz_0_clk;
// wire i_xadc_wiz_0_rstnn;
// wire i_xadc_wiz_0_rx4lawready;
// wire i_xadc_wiz_0_rx4lawvalid;
// wire [(32)-1:0] i_xadc_wiz_0_rx4lawaddr;
// wire i_xadc_wiz_0_rx4lwready;
// wire i_xadc_wiz_0_rx4lwvalid;
// wire [(32)-1:0] i_xadc_wiz_0_rx4lwdata;
// wire [(32/8)-1:0] i_xadc_wiz_0_rx4lwstrb;
// wire i_xadc_wiz_0_rx4lbready;
// wire i_xadc_wiz_0_rx4lbvalid;
// wire [(2)-1:0] i_xadc_wiz_0_rx4lbresp;
// wire i_xadc_wiz_0_rx4larready;
// wire i_xadc_wiz_0_rx4larvalid;
// wire [(32)-1:0] i_xadc_wiz_0_rx4laraddr;
// wire i_xadc_wiz_0_rx4lrready;
// wire i_xadc_wiz_0_rx4lrvalid;
// wire [(32)-1:0] i_xadc_wiz_0_rx4lrdata;
// wire [(2)-1:0] i_xadc_wiz_0_rx4lrresp;

/* DO NOT MODIFY THE ABOVE */
/* MUST MODIFY THE BELOW   */

xadc_wiz_0
#(
)
i_xadc_wiz_0
(
        .s_axi_aclk(i_xadc_wiz_0_clk),
        .s_axi_aresetn(i_xadc_wiz_0_rstnn),
        .s_axi_awready(i_xadc_wiz_0_rx4lawready),
        .s_axi_awvalid(i_xadc_wiz_0_rx4lawvalid),
        .s_axi_awaddr(i_xadc_wiz_0_rx4lawaddr),
        .s_axi_wready(i_xadc_wiz_0_rx4lwready),
        .s_axi_wvalid(i_xadc_wiz_0_rx4lwvalid),
        .s_axi_wdata(i_xadc_wiz_0_rx4lwdata),
        .s_axi_wstrb(i_xadc_wiz_0_rx4lwstrb),
        .s_axi_bready(i_xadc_wiz_0_rx4lbready),
        .s_axi_bvalid(i_xadc_wiz_0_rx4lbvalid),
        .s_axi_bresp(i_xadc_wiz_0_rx4lbresp),
        .s_axi_arready(i_xadc_wiz_0_rx4larready),
        .s_axi_arvalid(i_xadc_wiz_0_rx4larvalid),
        .s_axi_araddr(i_xadc_wiz_0_rx4laraddr),
        .s_axi_rready(i_xadc_wiz_0_rx4lrready),
        .s_axi_rvalid(i_xadc_wiz_0_rx4lrvalid),
        .s_axi_rdata(i_xadc_wiz_0_rx4lrdata),
        .s_axi_rresp(i_xadc_wiz_0_rx4lrresp),

        .vauxp0(xa_p0),
        .vauxn0(xa_n0),

        .ip2intc_irpt(),
        .channel_out(),
        .busy_out(),
        .eoc_out(),
        .eos_out(),
        .alarm_out(),
        .vp_in(),
        .vn_in()
);

//assign `NOT_CONNECT = i_xadc_wiz_0_clk;
//assign `NOT_CONNECT = i_xadc_wiz_0_rstnn;
//assign i_xadc_wiz_0_rx4lawready = 0;
//assign `NOT_CONNECT = i_xadc_wiz_0_rx4lawvalid;
//assign `NOT_CONNECT = i_xadc_wiz_0_rx4lawaddr;
//assign i_xadc_wiz_0_rx4lwready = 0;
//assign `NOT_CONNECT = i_xadc_wiz_0_rx4lwvalid;
//assign `NOT_CONNECT = i_xadc_wiz_0_rx4lwdata;
//assign `NOT_CONNECT = i_xadc_wiz_0_rx4lwstrb;
//assign `NOT_CONNECT = i_xadc_wiz_0_rx4lbready;
//assign i_xadc_wiz_0_rx4lbvalid = 0;
//assign i_xadc_wiz_0_rx4lbresp = 0;
//assign i_xadc_wiz_0_rx4larready = 0;
//assign `NOT_CONNECT = i_xadc_wiz_0_rx4larvalid;
//assign `NOT_CONNECT = i_xadc_wiz_0_rx4laraddr;
//assign `NOT_CONNECT = i_xadc_wiz_0_rx4lrready;
//assign i_xadc_wiz_0_rx4lrvalid = 0;
//assign i_xadc_wiz_0_rx4lrdata = 0;
//assign i_xadc_wiz_0_rx4lrresp = 0;

