package nl.keytech.reservation.spring;

import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.servlet.view.JstlView;

public class JstlTemplateView extends JstlView {
	protected String contentPage;

	public String getContentPage() {
		return contentPage;
	}

	public void setContentPage(String contentPage) {
		this.contentPage = contentPage;
	}
	
	@Override
	protected void exposeModelAsRequestAttributes(Map<String, Object> model, HttpServletRequest request) throws Exception {
		model.put("contentPage", contentPage);
		super.exposeModelAsRequestAttributes(model, request);
	}
	
}
